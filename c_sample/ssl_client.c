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

static SSL_CTX*         _g_ssl_context;

static void
app_ssl_global_init(void)
{
   SSL_library_init();           // load encryption & hash algorithms for SSL
   SSL_load_error_strings();     // load the error strings
}

static void
app_ssl_create_client_context(void)
{
   _g_ssl_context = SSL_CTX_new(SSLv3_method());
}

static void
app_ssl_load_cert_and_private_key(void)
{
   //SSL_CTX_use_certificate_file(_g_ssl_context, SERVER_CERTIFICATE, SSL_FILETYPE_PEM);
   //SSL_CTX_use_PrivateKey_file(_g_ssl_context, SERVER_PRIVATE_KEY, SSL_FILETYPE_PEM);

   // XXX check if the server cert and priv key matches

   // XXX load CA cert to verify client
   SSL_CTX_set_verify(_g_ssl_context, SSL_VERIFY_NONE, NULL);
   SSL_CTX_set_verify_depth(_g_ssl_context, 1);
}

static SSL*
app_ssl_create_client_ssl(int sd)
{
   SSL*     ssl;

   ssl = SSL_new(_g_ssl_context);
   if(ssl == NULL)
   {
      ERR_print_errors_fp(stderr);
      exit(1);
   }

   SSL_set_fd(ssl, sd);

   if(SSL_connect(ssl) == -1)
   {
      perror("SSL connect failed:");
      exit(1);
   }

   // XXX verify server certificate
   //SSL_get_peer_certificate(ssl);

   return ssl;
}

static void
app_init_client_ssl(void)
{
   // step 1. initialize SSL library
   app_ssl_global_init();

   // step 2. create SSL context
   app_ssl_create_client_context();

   // step 3. set up certificate and key for server
   app_ssl_load_cert_and_private_key();
}

static int
app_init_tcp_client_sock(void)
{
   int      sd;
   struct sockaddr_in   my_addr;

   sd = socket(AF_INET, SOCK_STREAM, 0);
   return sd;
}

int
main(int argc, char** argv)
{
   struct sockaddr_in   serv_addr;
   int                  sd;
   SSL*                 ssl;
   char                 buffer[4096];
   int                  ret;

   // initialize SSL
   app_init_client_ssl();

   // initialize TCP/IP client
   sd = app_init_tcp_client_sock();

   memset(&serv_addr, 0, sizeof(serv_addr));
   serv_addr.sin_family       = AF_INET;
   serv_addr.sin_port         = htons(atoi(argv[2]));
   serv_addr.sin_addr.s_addr  = inet_addr(argv[1]);

   // connect
   ret = connect(sd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
   if(ret != 0)
   {
      perror("connect failed:");
      return -1;
   }

   ssl = app_ssl_create_client_ssl(sd);
   printf ("SSL connection using %s\n", SSL_get_cipher (ssl));

   while(1)
   {
      ret = read(0, buffer, sizeof(buffer) - 1);
      if(ret <= 0)
      {
         close(sd);
         SSL_free(ssl);
         break;
      }

      printf("read %d bytes from stdin\n", ret);
      ret = SSL_write(ssl, buffer, ret);
      if(ret == -1)
      {
         ERR_print_errors_fp(stderr);
         printf("SSL_write error: %d\n", ret);
         close(sd);
         SSL_free(ssl);
         break;
      }

      ret = SSL_read(ssl, buffer, sizeof(buffer) - 1);
      if(ret == -1)
      {
         ERR_print_errors_fp(stderr);
         printf("SSL_read error: %d\n", ret);
         close(sd);
         SSL_free(ssl);
         break;
      }

      buffer[ret] = '\0';
      printf("read %d chars:'%s'\n", ret, buffer);
   }

   SSL_CTX_free(_g_ssl_context);
   return 0;
}
