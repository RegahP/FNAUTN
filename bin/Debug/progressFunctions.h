#ifndef PROGRESSFUNCTIONS_H_INCLUDED
#define PROGRESSFUNCTIONS_H_INCLUDED

void NewGame(){

    Progress progress;


    FILE *pArchivoProgress;
    pArchivoProgress = fopen("save.dat", "rb+");
    if(pArchivoProgress==NULL){
        pArchivoProgress = fopen("save.dat", "wb");
        fwrite(&progress, sizeof (progress), 1, pArchivoProgress);

        fclose(pArchivoProgress);
        pArchivoProgress = fopen("save.dat", "rb+");
    }

    fread(&progress, sizeof progress, 1, pArchivoProgress) == 1;
    progress.setNight(1);
    fseek(pArchivoProgress, 0, 0);
    fwrite(&progress, sizeof progress, 1, pArchivoProgress);

    fclose(pArchivoProgress);

}
int ContinueGame(){

    Progress progress;
    int night;


    FILE *pArchivoProgress;
    pArchivoProgress = fopen("save.dat", "rb");
    if(pArchivoProgress==NULL){
        cout<<"No se pudo abrir el archivo"<<endl;
    }

    fread(&progress, sizeof progress, 1, pArchivoProgress);
    night = progress.getNight();


    fclose(pArchivoProgress);

    return night;
}

void UpdateProgress(int num){

    Progress progress;

    FILE *pArchivoProgress;
    pArchivoProgress = fopen("save.dat", "rb+");
    if(pArchivoProgress==NULL){
        cout<<"No se pudo abrir el archivo"<<endl;
    }

    fread(&progress, sizeof progress, 1, pArchivoProgress);
    if(num <= 5){
        progress.setNight(num);
    }
    if(num == 6){
        progress.setNight5();
    }
    if(num == 7){
        progress.setNight6();
    }
    fseek(pArchivoProgress, 0, 0);
    fwrite(&progress, sizeof progress, 1, pArchivoProgress);

    fclose(pArchivoProgress);
}

Progress ReadProgress(){

    Progress progress;

    FILE *pArchivoProgress;
    pArchivoProgress = fopen("save.dat", "rb");
    if (pArchivoProgress==NULL){
        cout<<"NO SE PUDO ABRIR EL ARCHIVO"<<endl;
        pArchivoProgress = fopen("save.dat", "wb");
        fwrite(&progress, sizeof (progress), 1, pArchivoProgress);
        fclose(pArchivoProgress);
        return progress;
    }
    fseek(pArchivoProgress, 0, 0);
    fread(&progress, sizeof(Progress), 1, pArchivoProgress);
    fclose(pArchivoProgress);
    return progress;
}

void SaveSettings(Progress progress){

    FILE *pArchivoProgress;
    pArchivoProgress = fopen("save.dat", "rb+");
    if(pArchivoProgress==NULL){
        cout<<"No se pudo abrir el archivo"<<endl;
    }
    fseek(pArchivoProgress, 0, 0);
    fwrite(&progress, sizeof progress, 1, pArchivoProgress);

    fclose(pArchivoProgress);
}


#endif // PROGRESSFUNCTIONS_H_INCLUDED
