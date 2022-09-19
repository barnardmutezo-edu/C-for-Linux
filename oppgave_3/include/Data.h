#ifndef __Data_H__
#define __Data_H__

// A nodes attributes contained in a struct to keep code clean and scalable
typedef struct DATA
{
    unsigned char productName[50]; // Elementet skal også inneholde en tekststreng som inneholder VARENAVN
    int quantity; // en integer som inneholder ANTALL
    float pricePerUnit; // en float som inneholder PRIS PER VARE

} DATA;

#endif //__Data_H
