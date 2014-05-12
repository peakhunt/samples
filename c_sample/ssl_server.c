#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define     SERVER_CERTIFICATE      "stunnel.pem"
#define     SERVER_PRIVATE_KEY      "stunnel.pem"

#define     LOG(fmt, ...)           printf("%s:%d,"fmt, __FILE__, __LINE__, ##__VA_ARGS__)

#define RETURN_NULL(x) if ((x)==NULL) exit (1)
#define RETURN_ERR(err,s) if ((err)==-1) { perror(s); exit(1); }
#define RETURN_SSL(err) if ((err)==-1) { ERR_print_errors_fp(stderr); exit(1); }

static SSL_CTX*         _g_ssl_context;

static int              _g_serv_sd;

static void
app_ssl_global_init(void)
{
   LOG("initializing ssl global\n");
   SSL_library_init();           // load encryption & hash algorithms for SSL
   SSL_load_error_strings();     // load the error strings
}

static void
app_ssl_create_server_context(void)
{
   LOG("initializing ssl server context\n");
   _g_ssl_context = SSL_CTX_new(SSLv3_server_method());

   if(_g_ssl_context == NULL)
   {
      ERR_print_errors_fp(stderr);
      exit(1);
   }
}

static void
app_ssl_load_cert_and_private_key(void)
{
   LOG("loading server cert and private key\n");
   if(!SSL_CTX_use_certificate_file(_g_ssl_context, SERVER_CERTIFICATE, SSL_FILETYPE_PEM))
   {
      ERR_print_errors_fp(stderr);
      exit(1);
   }

   if(!SSL_CTX_use_PrivateKey_file(_g_ssl_context, SERVER_PRIVATE_KEY, SSL_FILETYPE_PEM))
   {
      ERR_print_errors_fp(stderr);
      exit(1);
   }

   // XXX check if the server cert and priv key matches

   // XXX load CA cert to verify client
   SSL_CTX_set_verify(_g_ssl_context, SSL_VERIFY_NONE, NULL);
   SSL_CTX_set_verify_depth(_g_ssl_context, 1);
}

static SSL*
app_ssl_create_ssl(int sd)
{
   SSL*     ssl;

   ssl = SSL_new(_g_ssl_context);
   if(ssl == NULL)
   {
      ERR_print_errors_fp(stderr);
      exit(1);
   }
   SSL_set_fd(ssl, sd);
   SSL_accept(ssl);

   return ssl;
}

static void
app_init_ssl(void)
{
   LOG("initializing SSL\n");
   // step 1. initialize SSL library
   app_ssl_global_init();

   // step 2. create SSL context
   app_ssl_create_server_context();

   // step 3. set up certificate and key for server
   app_ssl_load_cert_and_private_key();
   LOG("initializing SSL doe\n");
}

static void
app_init_tcp_server_sock(void)
{
   struct sockaddr_in   my_addr;

   _g_serv_sd = socket(AF_INET, SOCK_STREAM, 0);

   memset(&my_addr, 0, sizeof(my_addr));
   my_addr.sin_family      = AF_INET;
   my_addr.sin_addr.s_addr = INADDR_ANY;
   my_addr.sin_port        = htons(25555);

   bind(_g_serv_sd, (struct sockaddr*)&my_addr, sizeof(my_addr));

   listen(_g_serv_sd, 5);
}

int
main()
{
   struct sockaddr_in   cli_addr;
   int                  sd,
                        cli_addr_len = sizeof(cli_addr);
   SSL*                 ssl;
   char                 buffer[4096];
   int                  len;

   LOG("starting SSL sample server\n");
   // initialize SSL
   app_init_ssl();

   // initialize TCP/IP server
   app_init_tcp_server_sock();

   while(1)
   {
      sd    = accept(_g_serv_sd, (struct sockaddr*)&cli_addr, &cli_addr_len);
      LOG("got a new connection from %s:%d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

      ssl   = app_ssl_create_ssl(sd);

      // XXX verify client. but we don't do that

      while(1)
      {
         len = SSL_read(ssl, buffer, sizeof(buffer) - 1);
         if(len <= 0) 
         {
            ERR_print_errors_fp(stderr);
            printf("SSL_read error: %d\n", len);
            close(sd);
            SSL_free(ssl);
            break;
         }

         buffer[len] = '\0';
         printf("read %d chars:'%s'\n", len, buffer);

         len = SSL_write(ssl, buffer, len);
         if(len == -1)
         {
            ERR_print_errors_fp(stderr);
            printf("SSL_write error: %d\n", len);
            close(sd);
            SSL_free(ssl);
            break;
         }
      }
   }

   SSL_CTX_free(_g_ssl_context);
   return 0;
}
