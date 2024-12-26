#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct SinhVien{
    int id;
    char name[50];
    int age;
};
int writeFile(struct SinhVien *sv, int member);
int showSV(struct SinhVien *sv, int member);
int addSV(struct SinhVien *sv, int *member);
int fixSV(struct SinhVien *sv, int member);
int deleteSV(struct SinhVien *sv, int *member);
int searchSV(struct SinhVien *sv, int member);
int sortSV(struct SinhVien *sv, int member);
int main(){
    int choose=0;
    int member = 0;
    struct SinhVien sv[100];
    struct SinhVien sv1[100];
    printf("MENU\n");
    printf("1. In danh sach sinh vien\n");
    printf("2. Them sinh vien\n");
    printf("3. Sua thong tin sinh vien\n");
    printf("4. Xoa sinh vien\n");
    printf("5. Tim kiem sinh vien\n");
    printf("6. Sap xep danh sach sinh vien\n");
    printf("7. Thoat\n");
    do{
        printf("Lua chon cua ban: ");
        scanf("%d", &choose);
        getchar();
        switch(choose){
            case 1:
                showSV(sv, member);
                break;
            case 2:
                addSV(sv, &member);
                break;
            case 3:
                fixSV(sv, member);
                break;
            case 4:
                deleteSV(sv,&member);
                break;
            case 5:
                searchSV(sv,member);
                break;
            case 6:
                sortSV(sv,member);
                break;
            case 7:
                printf("Ban da chon thoat \n");
                break;
            default:
                printf("Lua chon cua ban khong co trong MENU \n");
        }
    }while(choose!=7);
}
int writeFile(struct SinhVien *sv, int member){
    FILE *file = fopen("sinhVien.bin", "wb");
    if (file == NULL) {
        printf("Khong the mo file de ghi.\n");
        return 1;
    }
    fwrite(&sv, sizeof(struct SinhVien), member, file);
    fclose(file);
    return 0;
}
int showSV(struct SinhVien *sv, int member){
    for(int i=0; i< member; i++){
            printf("ID: %d \t NAME: %s \t AGE: %d \n",sv[i].id, sv[i].name, sv[i].age );
    }
    return 0;
}

int addSV(struct SinhVien *sv, int *member){
    FILE *file;
    char name[50];
    if(*member == 0){
        file = fopen("sinhVien.bin","wb");
    }else{
        file = fopen("sinhVien.bin","ab");
    }
    
    printf("Moi ban them sinh vien \n");
    printf("Id sinh vien muon them: ");
    scanf("%d", &sv[*member].id);
    getchar();
    printf("Name sinh vien muon them: ");
    fgets(name, 50, stdin);
    strcpy(sv[*member].name, name);
    sv[*member].name[strcspn(sv[*member].name, "\n")] = '\0';
    printf("Tuoi sinh vien muon them: ");
    scanf("%d", &sv[*member].age);
    getchar();
    *member= *member +1;
    
    fwrite(&sv, sizeof(struct SinhVien), 1, file);
    
    if(file == NULL){
        printf("Loi luu sinh vien moi them vao file \n");
    }else{
        printf("Luu sinh vien moi thanh cong \n");
    }
    fclose(file);
    return 0;
}
int fixSV(struct SinhVien *sv, int member){
    int id=0;
    printf("Nhap ID sinh vien can sua: ");
        scanf("%d", &id);
        for (int i = 0; i < member; i++) {
            if (sv[i].id == id) {
                printf("Nhap ten moi: ");
                getchar();
                fgets(sv[i].name, sizeof(sv[i].name), stdin);
                sv[i].name[strcspn(sv[i].name, "\n")] = 0;
                printf("Nhap tuoi moi: ");
                scanf("%d", &sv[i].age);
                printf("Thong tin sinh vien da duoc cap nhat.\n");
                writeFile(sv, member);
                return 1;
            }
        }
        printf("Khong tim thay sainh vien \n");
    return 0;
}

int deleteSV(struct SinhVien *sv, int *member){
    int id;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);
    for (int i = 0; i < *member; i++) {
        if (sv[i].id == id) {
            for (int j = i; j < *member - 1; j++) {
                sv[j] = sv[j + 1];
            }
            *member= *member-1;
            writeFile(sv, *member);
            printf("Sinh vien da bi xoa.\n");
            return 1;
        }
    }
    printf("khong tim thay sinh vien \n");
    return 0;
}

int searchSV(struct SinhVien *sv, int member){
    char name[50];
    printf("Nhap ten sinh vien can tim: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    int flag = 0;
    for (int i = 0; i < member; i++) {
        if (strstr(sv[i].name, name) != NULL) {
            printf("ID: %d \t NAME: %s \t AGE: %d \n", sv[i].id, sv[i].name, sv[i].age);
            flag = 1;
        }
    }
    if (flag==0) {
        printf("Khong tim thay sinh vien.\n");
    }
    return 0;
}
int sortSV(struct SinhVien *sv, int member){
    for (int i = 0; i < member - 1; i++) {
        for (int j = i + 1; j < member; j++) {
            if (strcmp(sv[i].name, sv[j].name) > 0) {
                int temp= sv[i].id;
                sv[i].id= sv[j].id;
                sv[j].id=temp;
                char arr[50];
                strcpy(arr, sv[i].name);
                strcpy(sv[i].name,sv[j].name);
                strcpy(sv[j].name, arr);
                int count = sv[i].age;
                sv[i].age=sv[j].age;
                sv[j].age=count;
            }
        }
    }
    writeFile(sv, member);
    printf("Danh sach sinh vien da duoc sap xep theo ten.\n");
    return 0;
}
