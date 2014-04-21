#!/bin/bash

uuencode=1
binary=0

function untar_payload()
{
   match=$(grep --text --line-number '^PAYLOAD:$' $0 | cut -d ':' -f 1)
   payload_start=$((match + 1))
   if [[ $binary -ne 0 ]]
   then
      tail -n +$payload_start $0 | tar -tzvf -
   fi
   if [[ $uuencode -ne 0 ]]
   then
      tail -n +$payload_start $0 | uudecode | tar -tzvf -
   fi
}

read -p "Install files? " ans
if [[ "${ans:0:1}"  ||  "${ans:0:1}" ]]
then
   untar_payload

   # Do remainder of install steps.
   # as a demo, execute extracted hello
   ./hello
fi

exit 0
PAYLOAD:
begin 644 -
M'XL(`-]]5%,``^U8:6P;QQ6>7>J@+%FD'+N6CUA$2@-R`#*B;C=Q0EJ'ERY]
MQ)%[`%%6E$A);'@(Y#*64J,5H#@HX3@MBOYI_R0H^L._TOP(6J-!83IR8Z-P
M"Z9(`,-M42*(#<I)`#5172&HP[[9?;/D#*G$09$"+?@$ZNW[YGTS;ZXW.SL;
MCD83Y,N5+I"!OCZJ/0-]7>6:/O9U=0\03W=/=U_70/]`-_AYNOKZ!XBCZTN.
M2Y=T2@LF'0XR^W0D]EE^GU?^/RK?'PF,RI)DVC)YE%#+7N?5;2_BRJ82QTL&
MB17^[R&[2`/8]65^7N+E=!:K9MJ*?A;XU1D-8L->3N]&F&FI3-=S/?!R^NT&
MPFE"'":/0M<1O]XPP>DNC&-0YGDR\E:1MXK^3.<PL)S0OSK\[<;Z=K-^H1Y&
MO^$R?RK';VHA^GP-.WFMWLOI7O3K%7B/`\_L\CV('?5#T<AD?^]#T9`K&HFG
MYUWS@_VN_EYW*N'NUNNF?K1KAXZ>U/W9>#BP[:W$F$M:?NHEV^N.M;[@;Z_\
M[H'[WOCZ*XX_W.B1D"^1+R;-\-NR0=S5\`<(FS%!H']3M#O]9"ZMI8BJ4D"E
MFUY38\%(')"96"*.B$H.!?P'A]1N=[>[S^BO,8&2_E<:M_3.2!,M]:"=M4[H
MN@''@TD>\4;"CT&A#)?+\-4RO+P>9>D#JW*V?G.]@RAGLEI]84@'+UN7^>X6
M^SZI<Y#BWG_!?UN'%YZH/4N+5O)%D+T?49N&LI+3[=O4IB&L9,'T?.C/O/64
MDGE767IO]?B8_TKV55AYRI5+#EU=N0MYH?!K<%R;MG7`XKU@:YH@)Q67%92R
MM-ZJ9&Z>DL>7+^@Q0Z!KXQ=I43%OZUBDV`5KF?^E=0OX*YDWE$NW'U.DG/+6
M>AK(OS'(?P*RDGG3X+^+_,4#CT.\)-UV$IB%[T$@XV_6/PJ0]/$R[:^R=,`N
M@X.VQPQAZ\F+!=BMX%_,C:]\%RBV#K*2`DWKN'@9.E9XY]-B42>,+T^[;1W/
MZ6.IUY>).J\',B%G7CGG^J7D((%S>U\&I62>=.8"4%@(9#3G:B!SVKD.<S08
MV'?3ERGZ,W>42W<M_LP[GC\7?%"W<N9#;2>M+Y"Y'<C<&<X4?<6M?U&6EB5E
M__OIV\K9)YTPO5&G/7`VY&P/P),C<%9S=@;.GG9VP30/+F/_/U[&M8!3+\'J
M4?`,EW99'J9G)DT===#H:=##H`.@/=#=7X`>`WT9]'N@/R#&_M77][,GB#1O
MEW:U-%I_)#7:*4YS[^K=8O'!LO55W9\0)_HO@K^7.K3:1UO;#]N:3UD7R6,[
M'WZPQTFWJ.Y#<]X9B&L;!7RM]N?EH<T-QZ$B8M03@M\/H#Q#RP\_W_!"_72K
M=ZGQ7-V+EA_*\K=:K1C'"S0^\"O?/TQR>'Z]BIJ)).@6U.<MAM]FM%_#?+L#
M;79.[$*;Y?F=J/-8OELH_\>G1?WU:D(VZF-G5QYMEK,7T6;'[`'4S:C;46\C
MO+`<<17S!AL+!36;KT;4VU%/8'\9KJ#-XF;M-0DV#+?>GT[T+Z+-QG,5[3U8
M_M\2=AZ+<@OCN(.Z05@/3`X-#7W-T3D<GHP$XXY>]Z"[V^799SR(90/N'M?^
M?<8#(>[40DP+3H+6DH:>94^1N!9.SA%W/*&%W;Z#?I<6G$%K)IYV3Z8C<.Q&
M0D2W9H.I6>(.+<2A/D-K2:/DF7`R%4G$.4.%LF0X&J2.^#07U6B3$?BOA>?A
M_S084)8(!;4@<8=GU>ED,!969T/)DF4PU&`R&5PP&.SY.U-)/8Q@+#(%32<T
M_9_1BE'C9"I%W%.)6"P<U_[C^:/[BJXA<R_+.$_L_4GP%]\GODKXL[3TOF78
M#L&_3K`]`O\1Y#^"@/-S^#2GW8&US_@3R)\0XF?[G^TS)D>)L=<9?Q'YBPA,
M($[SA40J]^DWB)$+&#^/_#P"+)\P$<?O*6+L9<9G^W>/A8^7Q2\+^FEBY`9F
ML_S0B7S'!O$S>9888VKF+^0KR&?]%,>/X<\)?);?)I#/\B'EMU3AOTA*=P0J
M[#PXCWR6YYF(\Y\1^#GDYY#O%?SM@OZ)P&?W+SLV]'-APNR\27XF\-GY]1H.
M6)/@+\;_,N'W7Q;Y6>1O$OQ%_GF!7[JW&':OX"_R?R7P28,7M:'>%OS%]9.%
M7RLIG8>E^UUU?]&^!C];&9^=Y_E[Y%_'^!F_@/S"/?+_2OB[0^F>:=CL?LGF
ME_'9.K@EM,_N(UGK9[?/]/L"G[U/7$4'\5N,R%\3^.O(7[?R<8I\)I\@QOCT
MI=_0U?W%_%5$K").Y`]NP&>ZC?#W+29>UK[0H-@^MW;+Y&J;H=MQXNZ'GXM4
M?\^JUGX>7]@&A,J_R'W:0KUE;Q5<-L])'K>8YQ^/UYGG&H_7F^<5CS>8YQ"/
M-U9]/[3`J'16Q9O,\X#'-YEYGL>;S?S-XRUF7N;QS6:^Y?%6,X_RN,W,CSQN
M-_,>C[>5\AF';S'S%(_?9^8?'M]JYA4>WU;U_=="OF+F`1[?;NYO'F\W]RV/
M[S#W(X^+IZ*Q+NO(WXLBWJ*75<9/[U<RC+]7&'\WXG,"[D-<O-=]4Z^_%"?;
M']/Z<^5XGL-Z<D(]/]7]*^?EP@;]VJB_6;VLC>2$>?\CJ3X.9(-Z;NC_MU3$
M;^3KRGE?0W\Q_D:)^E?.^_T2]8;QQ'7+THQ+JOX]S:_CE>MD3*K^76Y:HKF_
MO6+]Q'3_ROV5VJ">'V,]8KLO;1#G*X"WR9!=A79?IWC9_F7O(;_'<7`@GD'\
MAM[N#F(7ZOD;^HMYXQ;ZB_W]"/WOHC^[Q_]S@_B;92-^L9[M<G5_CTSKKY+W
MII):2DM/3[NGB*H>'CJA!OQ/C*DJ"863X9E("FZHJA93IZ*)>#A%JD"J&DJH
M,]'$9#"JAK1$,J4&T_,$KGUST;`6#KG[>_9W5W=22]=)%:Z(R05B7$!#Z5AL
M`2AEEEJZA:+K+/VFI<<\>L)W9$0=.3H,01L]8,\<*434X6\?]1WQ#_$E^G==
MHAX*'#OH"ZC'1D>?&!E3QWP'`R,J^Q@\E4KKL1+5/W9$+0W,V)$A.@9CP<EH
MF-`[+U9&/R1[O>4?BM6P?B7&6L1/S(*O6E:5\/$9RE()=388#T&+JO\8%(0B
M<36="H?*@]5O^4:?635P&<=GXZ/VX6?4$]B-H6@PE=)G$CK$!H_VM&H_C<IK
;4I.:U*0F-:E)36I2DYK\'\J_`8G(,=<`*```
`
end
