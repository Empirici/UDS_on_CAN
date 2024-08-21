#ifndef CANMATRIX_H
#define CANMATRIX_H


typedef union
{
   unsigned char buff[8];
   struct
   {
    unsigned char LF   : 8;
    unsigned char LF_1 : 8;
    unsigned char LR   : 8;
    unsigned char LR_1 : 8;
    unsigned char RF   : 8;
    unsigned char RF_1 : 8;
    unsigned char RR   : 8;
    unsigned char RR_1 : 8;
   }bits;
}MSG_TPMS_375h_sig_u;


#endif // CANMATRIX_H
