00001 /*
00002  * Copyright (c) 2003 The OpenEvidence Project.  All rights reserved.
00003  *
00004  * Redistribution and use in source and binary forms, with or without
00005  * modification, are permitted provided that the following conditions
00006  * are met:
00007  *
00008  * 1. Redistributions of source code must retain the above copyright
00009  *    notice, this list of conditions, the following disclaimer,
00010  *    and the original OpenSSL and SSLeay Licences below. 
00011  *
00012  * 2. Redistributions in binary form must reproduce the above copyright
00013  *    notice, this list of conditions, the following disclaimer 
00014  *    and the original OpenSSL and SSLeay Licences below in
00015  *    the documentation and/or other materials provided with the
00016  *    distribution. 
00017  *
00018  * 3. All advertising materials mentioning features or use of this
00019  *    software must display the following acknowledgments:
00020  *    "This product includes software developed by the Openevidence Project
00021  *    for use in the OpenEvidence Toolkit. (http://www.openevidence.org/)"
00022  *    This product includes software developed by the OpenSSL Project
00023  *    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
00024  *    This product includes cryptographic software written by Eric Young
00025  *    (eay@cryptsoft.com).  This product includes software written by Tim
00026  *    Hudson (tjh@cryptsoft.com)."
00027  *
00028  * 4. The names "OpenEvidence Toolkit" and "OpenEvidence Project" must not be
00029  *    used to endorse or promote products derived from this software without
00030  *    prior written permission. For written permission, please contact
00031  *    openevidence-core@openevidence.org.
00032  *
00033  * 5. Products derived from this software may not be called "OpenEvidence"
00034  *    nor may "OpenEvidence" appear in their names without prior written
00035  *    permission of the OpenEvidence Project.
00036  *
00037  * 6. Redistributions of any form whatsoever must retain the following
00038  *    acknowledgments:
00039  *    "This product includes software developed by the OpenEvidence Project
00040  *    for use in the OpenEvidence Toolkit (http://www.openevidence.org/)
00041  *    This product includes software developed by the OpenSSL Project
00042  *    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
00043  *    This product includes cryptographic software written by Eric Young
00044  *    (eay@cryptsoft.com).  This product includes software written by Tim
00045  *    Hudson (tjh@cryptsoft.com)."
00046  *
00047  * THIS SOFTWARE IS PROVIDED BY THE OpenEvidence PROJECT ``AS IS'' AND ANY
00048  * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
00049  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
00050  * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenEvidence PROJECT OR
00051  * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
00052  * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
00053  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
00054  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
00055  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
00056  * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
00057  * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
00058  * OF THE POSSIBILITY OF SUCH DAMAGE.
00059  * ====================================================================
00060  *
00061  * This product includes software developed by the OpenSSL Project
00062  * for use in the OpenSSL Toolkit (http://www.openssl.org/)
00063  * This product includes cryptographic software written by Eric Young
00064  * (eay@cryptsoft.com).  This product includes software written by Tim
00065  * Hudson (tjh@cryptsoft.com).
00066  *
00067  */
00068 
00069 #include <oe/base_utils.h>
00070 
00071 #include <openssl/crypto.h>
00072 
00073 #include <string.h>
00074 #include <assert.h>
00075 #include <ctype.h>
00076 
00077 static const char base32EncodeTable[32] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
00078 
00079 static const unsigned char base32NumDecTable[10] = {
00080     -1, -1, 26, 27, 28, 29, 30, 31, -1, -1
00081 };
00082 
00083 static int makeMask(int bit_count)
00084 {
00085     int i;
00086     int ret = 0;
00087     
00088     for (i = 0; i < bit_count; i++) {
00089         ret <<= 1;
00090         ret |= 1;
00091     }
00092 
00093     return ret;
00094 }
00095 
00096 static void addBits(unsigned char *buf, int *bits_decoded, int bits)
00097 {
00098     int bits_to_first_byte;
00099     int shift_count;
00100     int buf_idx;
00101     int selected_bits;
00102 
00103     if (bits < 0)
00104         return;
00105     
00106     bits_to_first_byte = 8 - *bits_decoded % 8;
00107     if (bits_to_first_byte > 5)
00108         bits_to_first_byte = 5;
00109 
00110     shift_count = 8 - bits_to_first_byte - *bits_decoded % 8;
00111     buf_idx = *bits_decoded / 8;
00112     selected_bits = (bits & (makeMask(bits_to_first_byte) << 
00113                 (5 - bits_to_first_byte))) >> (5 - bits_to_first_byte);
00114     
00115     buf[buf_idx] |= selected_bits << shift_count;
00116     *bits_decoded += bits_to_first_byte;
00117 
00118     if (bits_to_first_byte < 5) {
00119         int bits_to_second_byte = 5 - bits_to_first_byte;
00120         
00121         shift_count = 8 - bits_to_second_byte;
00122         buf_idx++;
00123         selected_bits = bits & ((makeMask(bits_to_second_byte) << 
00124                     (5 - bits_to_second_byte)) >> (5 - bits_to_second_byte));
00125         
00126         buf[buf_idx] |= selected_bits << shift_count;
00127         *bits_decoded += bits_to_second_byte;
00128     }
00129 }
00130 
00131 unsigned char *OETS_base32Decode(const char *base32, size_t base32_len, 
00132         size_t *ret_len)
00133 {
00134     int bits_decoded = 0;
00135     size_t i;
00136     unsigned char *ret = NULL;
00137         
00138     assert(base32 != NULL && ret_len != NULL);
00139 
00140     if (base32_len == 0)
00141         base32_len = strlen(base32);
00142 
00143     ret = OPENSSL_malloc(base32_len * 5 / 8 + 2);
00144     if (ret == NULL)
00145         goto error;
00146     memset(ret, 0, base32_len * 5 / 8 + 2);
00147     
00148     for (i = 0; i < base32_len; i++) {
00149         if (base32[i] == '=')
00150             break;
00151         if (isalpha(base32[i]))
00152             addBits(ret, &bits_decoded, toupper(base32[i]) - 'A');
00153         if (isdigit(base32[i]))
00154             addBits(ret, &bits_decoded, base32NumDecTable[base32[i] - '0']);
00155     }
00156     
00157 #if 0
00158     TODO: should we check the padding?
00159     for (; i < base32_len; i++) {
00160         if (base32[i] == '=')
00161             pad_count++;
00162         else
00163             break;
00164     }
00165 #endif
00166     
00167     /* This operation also truncates extra bits from the end (when input
00168      * bit count was not divisible by 5). */
00169     *ret_len = bits_decoded / 8;
00170     return ret;
00171     
00172 error:
00173     OPENSSL_free(ret);
00174     return NULL;
00175 }
00176 
00177 /* Returns -1 when EOF is encountered. */
00178 static int readNextBits(const unsigned char *data, size_t data_len,
00179         int bits_read)
00180 {
00181     int ret = 0;
00182     int first_byte_bits;
00183     size_t byte_to_read;
00184     int shift_count;
00185     
00186     byte_to_read = bits_read / 8;
00187 
00188     if (byte_to_read >= data_len)
00189         return -1;
00190     
00191     first_byte_bits = 8 - (bits_read - byte_to_read * 8);
00192     if (first_byte_bits > 5)
00193         first_byte_bits = 5;
00194     shift_count = 8 - bits_read % 8 - first_byte_bits;
00195     ret = (data[byte_to_read] & (makeMask(first_byte_bits) << shift_count)) >> 
00196             shift_count;
00197 
00198     byte_to_read++;
00199     if (first_byte_bits < 5) {
00200         int second_byte_bits = 5 - first_byte_bits;
00201         ret <<= second_byte_bits;
00202     
00203         if (byte_to_read < data_len) {
00204             shift_count = 8 - second_byte_bits;
00205             ret |= (data[byte_to_read] & (makeMask(second_byte_bits) << 
00206                         shift_count)) >> shift_count;
00207         } 
00208     }
00209 
00210     return ret;
00211 }
00212 
00213 char *OETS_base32Encode(const unsigned char *data, size_t data_len)
00214 {
00215     char *ret = NULL;
00216     int next_bits;
00217     size_t bits_read;
00218     int ret_len = 0;
00219     
00220     assert(data != NULL && data_len != 0);
00221 
00222     ret = OPENSSL_malloc((data_len / 5) * (8 + 1) + 8 + 1);
00223     if (ret == NULL)
00224         goto error;
00225     
00226     for (bits_read = 0; 
00227             (next_bits = readNextBits(data, data_len, bits_read)) != -1; 
00228             bits_read += 5) {
00229         ret[ret_len++] = base32EncodeTable[next_bits];
00230 
00231         if (ret_len % 9 == 8 && bits_read + 5 < data_len * 8)
00232             ret[ret_len++] = '-';
00233     }
00234 
00235     /* Pad output. */
00236     while (bits_read % 40 != 0) {
00237         ret[ret_len++] = '=';
00238         bits_read += 5;
00239     }
00240 
00241     ret[ret_len++] = '\0';
00242     
00243     return ret;
00244     
00245 error:
00246     OPENSSL_free(ret);
00247     return NULL;
00248 }
00249 

Generated on Wed Mar 19 11:00:26 2003 for OE_len++] = '\0';
00242     
00243     return ret;
00244     
00245 error:
00246     OPENSSL_free(ret);
00247     return NULL;
00248 }