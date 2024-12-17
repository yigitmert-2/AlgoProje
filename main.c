#include <stdio.h>

int main() {
    FILE *fp = fopen("gunluk.dat","r"); //okuma modunda "gunluk.dat" dosyasını açar.
    FILE *fpgec = fopen("gec.dat", "w"); //yazma modunda "gec.dat" dosyasının açar.
    FILE *fperken = fopen("erken.dat", "w"); //yazma modunda "erken.dat" dosyasını açar.
    if (fp == NULL) { //"gunluk.dat" dosyasının başarılı bir şekilde açılıp açılmadığını kontrol eder.
        printf("Dosya acilamadi.\n");
        return 1;
    }
    if (fpgec == NULL) { //"gec.dat" dosyasının başarılı bir şekilde açılıp açılmadığını kontrol eder.
        printf("Dosya acilamadi.\n");
        return 1;
    }
    if (fperken == NULL) { //"erken.dat" dosyasının başarılı bir şekilde açılıp açılmadığını kontrol eder.
        printf("Dosya acilamadi.\n");
        return 1;
    }
    int sicil,saat,dakika,kalan_dakika;  //ihtiyacımız olacak değişkenlerin atanması.
    char girmecikma,bosluk;
    int en_erken_sicil,en_erken_dakika = 0,en_gec_sicil,en_gec_dakika = 0;
    char satir[128];
    while(fgets(satir,sizeof(satir),fp) != NULL) {  //fgets "gunluk.dat" dosyasını okur ver satir değişkenine atar. Bu işlem başarılı olduğu sürece döngü döner.
        sscanf(satir,"%d%d:%d%c%c",&sicil,&saat,&dakika,&bosluk,&girmecikma); //satir değişkeninden verileri okur.
        if(girmecikma == '<'){ //giriş yapmış olan çalışanları kontrol eder.
            if (saat >= 9) {
                kalan_dakika = (saat-9)*60 + dakika;
                if(en_gec_dakika<=kalan_dakika) {
                    en_gec_dakika = kalan_dakika;
                    en_gec_sicil = sicil;
                }
            }
        }
        if(girmecikma == '>') { //çıkış yapmış çalışanları kontrol eder.
            if(saat < 17) {
                kalan_dakika = (17-saat)*60 - dakika;
                if(en_erken_dakika<=kalan_dakika) {
                    en_erken_dakika = kalan_dakika;
                    en_erken_sicil = sicil;
                }
            }
        }
    }
    fprintf(fpgec,"%d %d\n",en_gec_sicil,en_gec_dakika);
    fprintf(fperken,"%d %d\n",en_erken_sicil,en_erken_dakika);

    fclose(fp);  //açtığımız dosyaları kapatır.
    fclose(fpgec);
    fclose(fperken);
    return 0;
}
