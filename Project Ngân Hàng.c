#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_ACCOUNT 100
#define MAX_TRANSACTION 1000




void toLowerStr(char *s) {
    for (int i = 0; s[i]; i++) {
        s[i] = tolower(s[i]);
    }
}
struct Account {
	char accountId [20]; 		 
	char fullName [50];			
	char phone [15];
	double balance;
	int status;
};

struct Transaction {
	char transId [20];
	char senderId [20];
	char receiverId [20];
	double amount;
	char type [10];
	char date [20];
};

int confirmTransaction() {
    while (1) {
        printf("Ban co chac chan muon thuc hien giao dich? (1 = Xac nhan, 2 = Huy): ");
        char buf[16];
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            printf("Loi doc du lieu. Vui long nhap lai.\n");
            continue;
        }
        buf[strcspn(buf, "\n")] = 0;
        if (strlen(buf) == 0) {
            printf("Khong duoc de trong. Vui long nhap lai.\n");
            continue;
        }
        int choice = atoi(buf);
        if (choice == 1 || choice == 2) return choice;
        printf("Lua chon khong hop le. Hay nhap 1 hoac 2.\n");
    }
}

struct Transaction addTran[MAX_TRANSACTION];
int transaction_size = 0;


struct Account addAccounts [MAX_ACCOUNT];
int Account_size = 0;
char findID[20];
int i;

char* trim(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
    return str;
}

int DuplicateID (char id[]){           // check id trung...
	int i;
	for ( i = 0; i < Account_size; i++){
		if (strcmp(addAccounts[i].accountId,id)==0) 
			return 1;
		}
		return 0;
	}
int notId(char str[]){
    char *s = trim(str); // lo?i b? kho?ng tr?ng d?u/cu?i
    if (strlen(s) == 0) return 0;   //check id khong dc am 
	
	 for (int i = 0; i < strlen(str); i++) {
        char c = str[i];
        // Chi cho phép chu cái (A-Z, a-z) và s? (0-9)
        if (!((c >= '0' && c <= '9') ||
              (c >= 'A' && c <= 'Z') ||
              (c >= 'a' && c <= 'z'))) {
            return 0; // gap ký tu dac biet => sai
        }
    }
    return 1; // 
}

	
int DuplicatePhone(char phone[], int excludeIndex) {    // check so dien thoai trung
    int i;
    for (i = 0; i < Account_size; i++) {
        if (i == excludeIndex) continue; 
        if (strcmp(addAccounts[i].phone, phone) == 0) {
            return 1; 
        }
    	}
    return 0; 
}
int notNumber(char str[]){  // check so dien thoai co phai ky tu hay khong
	int i;
	for ( i = 0; i < strlen (str) ; i++){
		if ( str[i] < '0' || str[i] > '9' ){
			return 0;
		}
		}
		return 1;
}

int notName(char str[]){           // cho phep nhap ten chu hoa chu thuong va khoang trang
	int i;
	for (int i = 0; i < strlen(str); i++) {
        char c = str[i];

        
        if ( (c >= 'A' && c <= 'Z') ||
             (c >= 'a' && c <= 'z') ||
             c == ' ' ) {
            continue;
        }	 
		return 0;
    }

    return 1;
}	

//Case 1:
	
void newAccount (){
	if (Account_size >= MAX_ACCOUNT){   // check id max chua
		printf ("So luong tai khoan da dat gioi han.\n");
			return ;
		}		
		while (getchar() != '\n');
		
 		struct Account addAccount; // acc 
 	 	
 	while (1){
 	 	printf ("Moi ban nhap ma tai khoan: ");   // nhap vao ma 
		fgets(addAccount.accountId,sizeof(addAccount.accountId),stdin);
	 	addAccount.accountId[strcspn(addAccount.accountId, "\n")] = 0;
	 	strcpy(addAccount.accountId, trim(addAccount.accountId));
	 	if (strlen(addAccount.accountId) == 0){                // check id trong        
	 		printf ("Ma tai khoan khong duoc de trong !\n");
	 		continue;
	 	}if (!notId(addAccount.accountId)){            // notid o tren nham check id am
				printf ("Id khong duoc nhap am va chua ky tu dac biet!!!\n");   
				continue;
	 	}if (DuplicateID(addAccount.accountId)) {      // duplicate ID check id trung
	 		printf("Ma tai khoan da ton tai, vui long nhap lai!\n");
            continue;
        }
		break;    
	}
		
while (1) {
        printf("Nhap ho va ten: ");
        fgets(addAccount.fullName, sizeof(addAccount.fullName), stdin);
        addAccount.fullName[strcspn(addAccount.fullName, "\n")] = 0;
		 strcpy(addAccount.fullName, trim(addAccount.fullName));


        if (strlen(addAccount.fullName) == 0) {
            printf("Ten khong duoc de trong!\n");
            continue;
        }
        if (!notName(addAccount.fullName)) {
            printf("Ten chi duoc chua chu cai va khoang trang!\n");
            continue;
        }
        break;
    }
	
	while (1){
	 	
	
		printf ("Moi ban nhap so dien thoai: ");
		fgets (addAccount.phone,sizeof(addAccount.phone),stdin);
		addAccount.phone[strcspn(addAccount.phone, "\n")] = 0;
				if (strlen(addAccount.phone) == 0){          // check sdt khong dc trong
					printf ("So dien thoai khong duoc de trong !\n");  
					continue;
				}if (!notNumber(addAccount.phone)){    //  notnum check xem sdt co ky tu khong 
					printf ("So dien thoai khong duoc nhap ki tu .Va khoang trong !!!\n");
					continue;
				}if (DuplicatePhone(addAccount.phone, -1)) {  //  duplicate check sdt da ton tai chua
            		printf("So dien thoai da ton tai, vui long nhap lai!\n");    
            		continue;	
		}break;
	}
		
		addAccount.balance = 100000;
		addAccount.status = 1;
		
		addAccounts[Account_size++] = addAccount;
		printf ("Da them tai khoan thanh cong");
		
}

// Case 2:
	
void updateAccounts() {                     
	while (getchar() != '\n');
	char id[20];
	int i,index;
	while (1) {
    printf("Nhap ID tai khoan can cap nhat: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    if (strlen(id) == 0) {
        printf("ID khong duoc de trong! Vui long nhap lai.\n");
        continue;
    }

    if (!notId(id)) {
        printf("ID chi duoc chua chu va so, khong duoc ky tu dac biet! Vui long nhap lai.\n");
        continue;
    }   // ID hop le	
	int index = -1; 
    for (i = 0; i < Account_size; i++) {
        if (strcmp(addAccounts[i].accountId, id) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Khong tim thay tai khoan! Vui long nhap lai.\n");           // check tk co ton tai khong
        continue;
    }
	break;
}

    printf("\n ====== Cap nhat thong tin tai khoan ======\n");
    printf("Ma TK : %s \n", addAccounts[index].accountId);
    printf("Ten : %s \n", addAccounts[index].fullName);
    printf("SDT: %s \n", addAccounts[index].phone);
   
    char newName[50];  // khai bao ten moi
    while (1) {
        printf("Nhap ten moi ( Khong nhap la giu nguyen ): ");
        fgets(newName, sizeof(newName), stdin);
        newName[strcspn(newName, "\n")] = 0;
        
         strcpy(addAccounts[index].fullName, trim(addAccounts[index].fullName));
		
        if (strlen(newName) == 0) {               // check name trong
            break; 
        }
        if (!notName(newName)){                 //not name check ten nhap so
        printf ("Ten chi duoc chu va khoang trang!!!\n");
        continue;
		}
        strcpy(addAccounts[index].fullName, newName);
        break;
    }

    
    char newPhone[15];  // khai bao sdt moi
    while (1) {
        printf("Nhap so dien thoai moi ( Khong nhap la giu nguyen ): ");
        fgets(newPhone,sizeof(newPhone), stdin);
        newPhone[strcspn(newPhone, "\n")] = 0;

        if (strlen(newPhone) == 0) {         // check kh nhao thi giu nguyen
        break;
        }
         if (!notNumber(newPhone)) {
        printf("So dien thoai chi duoc nhap so!\n");       // notnumber  check kh dc nhap ki tu
        continue; 
    	}if (DuplicatePhone(newPhone, index)) {
        printf("So dien thoai da ton tai, vui long nhap lai!\n");   //  duplucate check sdt da ton tai
        continue;
    	}
		strcpy(addAccounts[index].phone, newPhone);
        break;
    }

    printf("\n Cap nhat thanh cong! \n");
}


	void flush_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Case 3:

void manageStatus() {
    flush_stdin();

    char id[20];
    int index = -1;
    while (1) {
        printf("Nhap ID tai khoan muon thay doi trang thai: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = 0;

        if (strlen(id) == 0) {
            printf("ID khong duoc de trong! Vui long nhap lai.\n");
            continue;
        }

        index = -1;
        for (int i = 0; i < Account_size; i++) {
            if (strcmp(addAccounts[i].accountId, id) == 0) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            printf("Khong tim thay tai khoan! Vui long nhap lai.\n");
            continue;
        }

        break;
    }

    printf("\n===== Thong tin tai khoan =====\n");
    printf("ID: %s\n", addAccounts[index].accountId);
    printf("Ten: %s\n", addAccounts[index].fullName);
    printf("SDT: %s\n", addAccounts[index].phone);
    printf("Trang thai: %s\n", addAccounts[index].status == 1 ? "Hoat dong" : "Bi khoa");

    printf("\n----- Chon thao tac -----\n");
    printf("1. Khoa tai khoan\n");
    printf("2. Mo khoa tai khoan\n");
    printf("3. Xoa tai khoan\n");
    printf("4. Huy\n");

    int choose;
    while (1) {
        printf("Nhap lua chon: ");
        char buf[16];
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            printf("Loi doc du lieu. Vui long nhap lai.\n");
            continue;
        }
        buf[strcspn(buf, "\n")] = 0;
        if (strlen(buf) == 0) {
            printf("Khong duoc de trong. Vui long chon 1-4.\n");
            continue;
        }
        choose = atoi(buf);
        if (choose >= 1 && choose <= 4) break;
        printf("Lua chon khong hop le. Vui long chon 1-4.\n");
    }

    // Helper to read confirmation (1 = confirm, 2 = cancel)
    int read_confirmation() {
        while (1) {
            printf("Nhap lua chon (1 = Xac nhan, 2 = Huy): ");
            char cbuf[16];
            if (fgets(cbuf, sizeof(cbuf), stdin) == NULL) {
                printf("Loi doc du lieu. Vui long nhap lai.\n");
                continue;
            }
            cbuf[strcspn(cbuf, "\n")] = 0;
            if (strlen(cbuf) == 0) {
                printf("Khong duoc de trong. Vui long nhap lai.\n");
                continue;
            }
            int v = atoi(cbuf);
            if (v == 1 || v == 2) return v;
            printf("Lua chon khong hop le. Hay nhap 1 hoac 2.\n");
        }
    }

    if (choose == 1) {
        if (addAccounts[index].status == 0) {
            printf("Tai khoan da bi khoa truoc do.\n");
            return;
        }
        printf("----- XAC NHAN KHOA TAI KHOAN -----\n");
        printf("Ban chac chan muon khoa tai khoan ID: %s - %s ?\n", addAccounts[index].accountId, addAccounts[index].fullName);
        printf("1. Khoa\n2. Huy\n");
        int conf = read_confirmation();
        if (conf != 1) {
            printf("Da huy thao tac khoa.\n");
            return;
        }
        addAccounts[index].status = 0;
        printf(">>> Tai khoan %s da bi KHOA!\n", addAccounts[index].accountId);
        return;
    }

    if (choose == 2) {
        if (addAccounts[index].status == 1) {
            printf("Tai khoan da dang hoat dong.\n");
            return;
        }
        printf("----- XAC NHAN MO TAI KHOAN -----\n");
        printf("Ban chac chan muon mo tai khoan ID: %s - %s ?\n", addAccounts[index].accountId, addAccounts[index].fullName);
        printf("1. Mo\n2. Huy\n");
        int conf = read_confirmation();
        if (conf != 1) {
            printf("Da huy thao tac mo.\n");
            return;
        }
        addAccounts[index].status = 1;
        printf(">>> Tai khoan %s da duoc MO KHOA!\n", addAccounts[index].accountId);
        return;
    }

    if (choose == 3) {
        printf("----- XAC NHAN XOA TAI KHOAN -----\n");
        printf("Ban chac chan muon xoa tai khoan ID: %s - %s ?\n", addAccounts[index].accountId, addAccounts[index].fullName);
        printf("1. Xoa\n2. Huy\n");
        int conf = read_confirmation();
        if (conf != 1) {
            printf("Da huy thao tac xoa.\n");
            return;
        }
        for (int j = index; j < Account_size - 1; j++) {
            addAccounts[j] = addAccounts[j + 1];
        }
        Account_size--;
        printf(">>> Da xoa tai khoan thanh cong!\n");
        return;
    }

    if (choose == 4) {
        printf("Da huy thao tac.\n");
        return;
    }

    printf("Lua chon khong hop le.\n");
}
// case 4:

void searchAccount() {
    flush_stdin();   // Xóa b? nh? d?m tru?c khi nh?p

    char keyword[50];
    int found;

    while (1) {
        found = 0;
        printf("\n----- TRA CUU TAI KHOAN -----\n");
        printf("Nhap tu khoa tim kiem (ID hoac Ten): ");
        fgets(keyword, sizeof(keyword), stdin);
        keyword[strcspn(keyword, "\n")] = 0;

        if (strlen(keyword) == 0) {
            printf("Tu khoa khong duoc de trong! Vui long nhap lai.\n");
            continue;
        }

        // 1) Tim theo ID (khong phan biet hoa/thuong)
        for (int i = 0; i < Account_size; i++) {
            char idLower[20];
            strncpy(idLower, addAccounts[i].accountId, sizeof(idLower));
            idLower[sizeof(idLower)-1] = '\0';
            toLowerStr(idLower);

            char keyLower[20];
            strncpy(keyLower, keyword, sizeof(keyLower));
            keyLower[sizeof(keyLower)-1] = '\0';
            toLowerStr(keyLower);

            if (strcmp(idLower, keyLower) == 0) {
                printf("\n--- Ket qua (tim theo ID) ---\n");
                printf("ID: %s\n", addAccounts[i].accountId);
                printf("Ten: %s\n", addAccounts[i].fullName);
                printf("SDT: %s\n", addAccounts[i].phone);
                printf("Trang thai: %s\n", addAccounts[i].status == 1 ? "Hoat dong" : "Bi khoa");
                found = 1;
                break;
            }
        }

        // 2) Tim theo Ten (PHAN BIET CHU HOA/THUONG)
        if (!found) {
            for (int i = 0; i < Account_size; i++) {
                if (strstr(addAccounts[i].fullName, keyword) != NULL) {
                    if (found == 0) printf("\n--- Ket qua (tim theo Ten) ---\n");
                    found++;
                    printf("[%d] ID: %s | Ten: %s | SDT: %s | Trang thai: %s\n",
                           found,
                           addAccounts[i].accountId,
                           addAccounts[i].fullName,
                           addAccounts[i].phone,
                           addAccounts[i].status == 1 ? "Hoat dong" : "Bi khoa");
                }
            }
        }

        if (!found) {
            printf("Khong co ket qua phu hop! Vui long nhap lai.\n");
            continue;
        }

        break; // tim thay -> thoat
    }
}

// Case 5:

	void listAccounts(struct Account accounts[], int size) {
    if (size == 0) {
        printf("Chua co tai khoan nao trong he thong!\n");
        return;
    }

    flush_stdin();

    int pageSize;
    char temp[64];

    
    while (1) {
        printf("Nhap so luong phan tu hien thi tren moi trang (page_size > 0): ");
        if (fgets(temp, sizeof(temp), stdin) == NULL) continue;
        temp[strcspn(temp, "\n")] = '\0';
        pageSize = atoi(temp);
        if (pageSize > 0) break;
        printf("khong hop le! Moi nhap lai !!!.\n");
    }

    int totalPages = (size + pageSize - 1) / pageSize;
    int currentPage = 0;
    char input[64];

    while (1) {
        int start = currentPage * pageSize;
        int end = start + pageSize;
        if (end > size) end = size;

        printf("\n------------------------- Danh sach tai khoan (%d/%d) --------------------------------\n", currentPage + 1, totalPages);
        printf("----------------------------------------------------------------------------------------------\n");
        printf("| %-4s | %-15s | %-25s | %-12s | %-10s | %-10s |\n",
               "STT", "ID", "Ho ten", "Phone", "So du", "Trang thai");
        printf("----------------------------------------------------------------------------------------------\n");

        for (int i = start; i < end; i++) {
            printf("| %-4d | %-15s | %-25s | %-12s | %-10.2f | %-10s |\n",
                   i + 1,   // STT theo toàn danh sách
                   accounts[i].accountId,
                   accounts[i].fullName,
                   accounts[i].phone,
                   accounts[i].balance,
                   accounts[i].status == 1 ? "Hoat dong" : "Bi khoa");
        }
        printf("----------------------------------------------------------------------------------------------\n");

        while (1) {
            printf("|| 'N' trang sau || 'P' trang truoc || 'Q' thoat || So trang de nhay den ||\n");
            printf("Nhap lua chon: ");

            if (fgets(input, sizeof(input), stdin) == NULL) {
                printf("Loi khi doc du lieu. Huy.\n");
                return;
            }
            input[strcspn(input, "\n")] = '\0';

            if (strlen(input) == 1) {
                char c = input[0];
                if (c == 'n' || c == 'N') {
                    if (currentPage + 1 < totalPages) currentPage++;
                    else printf("Ban dang o trang cuoi!\n");
                    break;
                } else if (c == 'p' || c == 'P') {
                    if (currentPage > 0) currentPage--;
                    else printf("Ban dang o trang dau!\n");
                    break;
                } else if (c == 'q' || c == 'Q') {
                    return;
                }
            }

            int pageNum = atoi(input);
            if (pageNum > 0 && pageNum <= totalPages) {
                currentPage = pageNum - 1;
                break;
            }

            if (pageNum <= 0) {
                printf("Khong hop le.vui long chon lai!\n");
                continue;
            }

            printf("Nhap khong hop le! Vui long thu lai.\n");
        }
    }
}

//Case 6:
void sortAccounts(struct Account accounts[], int size) {
	
    if (size == 0) {
        printf("\n Khong co du lieu de sap xep!\n");
        return;
    }
	
	flush_stdin(); 
	
    char input[20];
    int choice;

    // ============================
    // INPUT + VALIDATION FULL
    // ============================
    while (1) {
    printf("\n----- SAP XEP DANH SACH -----\n");
    printf("1. Theo so du giam dan\n");
    printf("2. Theo ten A-Z\n");
    printf("Moi ban chon: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Loi doc du lieu! Nhap lai.\n");
        continue;
    }

    input[strcspn(input, "\n")] = 0;  // b? xu?ng dòng

    if (strlen(input) == 0) {
        printf("Khong duoc de trong! Moi nhap lai.\n");
        continue;
    }

    int num = atoi(input);

    if (num == 1 || num == 2) {
        choice = num;
        break;
    }

    printf("Lua chon chi co 1 hoac 2! Moi nhap lai.\n");
}


    // ============================
    // SAP XEP THEO SO DU GIAM DAN
    // ============================
    if (choice == 1) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                if (accounts[i].balance < accounts[j].balance) {
                    struct Account temp = accounts[i];
                    accounts[i] = accounts[j];
                    accounts[j] = temp;
                }
            }
        }
    }

    // ============================
    // SAP XEP TEN A-Z
    // ============================
    else if (choice == 2) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                if (strcasecmp(accounts[i].fullName, accounts[j].fullName) > 0) {
                    struct Account temp = accounts[i];
                    accounts[i] = accounts[j];
                    accounts[j] = temp;
                }
            }
        }
    }

    printf("\n Da sap xep xong!\n");
}
 //case 7: chuyen xien
//case 7: chuyen tien
void Transactions() {
    flush_stdin();
    printf("\n=========== Chuyen khoan ===========\n");

    if (Account_size < 2) {
        printf("Can it nhat 2 tai khoan de thuc hien giao dich!\n");
        return;
    }

    char sendId[20], receiveId[20];
    double money;
    int senderIndex = -1, receiverIndex = -1;

    // --- Nhap ID nguoi gui ---
    while (1) {
        printf("Nhap ID tai khoan chuyen tien: ");
        fgets(sendId, sizeof(sendId), stdin);
        sendId[strcspn(sendId, "\n")] = 0;

        if (strlen(sendId) == 0) {
            printf("ID khong duoc de trong!\n");
            continue;
        }

        senderIndex = -1;
        for (int i = 0; i < Account_size; i++) {
            if (strcmp(addAccounts[i].accountId, sendId) == 0) {
                senderIndex = i;
                break;
            }
        }

        if (senderIndex == -1) {
            printf("Khong tim thay tai khoan nguoi gui!\n");
            continue;
        }

        if (addAccounts[senderIndex].status == 0) {
            printf("Tai khoan nay dang bi KHOA, khong the thuc hien giao dich!\n");
            return;
        }

        break;
    }

    // --- Nhap ID nguoi nhan ---
    while (1) {
        printf("Nhap ID tai khoan nhan tien: ");
        fgets(receiveId, sizeof(receiveId), stdin);
        receiveId[strcspn(receiveId, "\n")] = 0;

        if (strlen(receiveId) == 0) {
            printf("ID khong duoc de trong!\n");
            continue;
        }

        if (strcmp(sendId, receiveId) == 0) {
            printf("Khong the chuyen tien cho chinh minh!\n");
            continue;
        }

        receiverIndex = -1;
        for (int i = 0; i < Account_size; i++) {
            if (strcmp(addAccounts[i].accountId, receiveId) == 0) {
                receiverIndex = i;
                break;
            }
        }

        if (receiverIndex == -1) {
            printf("Khong tim thay tai khoan nguoi nhan!\n");
            continue;
        }

        if (addAccounts[receiverIndex].status == 0) {
            printf("Tai khoan nguoi nhan dang bi KHOA, khong the nhan tien!\n");
            continue;
        }

        break;
    }

    // --- Nhap so tien ---
    while (1) {
        printf("Nhap so tien: ");
        if (scanf("%lf", &money) != 1) {
            flush_stdin();
            printf("So tien khong hop le!\n");
            continue;
        }
        flush_stdin();

        if (money <= 0) {
            printf("So tien phai lon hon 0!\n");
            continue;
        }

        if (addAccounts[senderIndex].balance < money) {
            printf("So du khong du! (Hien co: %.2lf)\n", addAccounts[senderIndex].balance);
            continue;
        }

        break;
    }

    // --- Hien thi thong tin giao dich va xac nhan ---
    printf("\nThong tin giao dich:\n");
    printf("Nguoi gui: %s\n", addAccounts[senderIndex].fullName);
    printf("Nguoi nhan: %s\n", addAccounts[receiverIndex].fullName);
    printf("So tien: %.2lf\n", money);

    int conf = confirmTransaction();
    if (conf != 1) {
        printf("Da huy giao dich.\n");
        return;
    }

    // --- Cap nhat so du sau khi xac nhan ---
    addAccounts[senderIndex].balance -= money;
    addAccounts[receiverIndex].balance += money;

    // --- Luu giao dich ---
    if (transaction_size < MAX_TRANSACTION) {
        strcpy(addTran[transaction_size].senderId, sendId);
        strcpy(addTran[transaction_size].receiverId, receiveId);
        addTran[transaction_size].amount = money;
        strcpy(addTran[transaction_size].type, "Transfer");
        transaction_size++;
    }

    printf(">>> Giao dich thanh cong!\n");
    printf("So du moi cua nguoi gui: %.2lf\n", addAccounts[senderIndex].balance);
}

// case 8:
void viewTransactionHistory() {
    flush_stdin();

    char targetId[20];
    int exist = 0;

    printf("\n===== XEM LICH SU GIAO DICH =====\n");

    // --- Nh?p mã tài kho?n ---
    while (1) {
        printf("Nhap ID tai khoan: ");
        fgets(targetId, sizeof(targetId), stdin);
        targetId[strcspn(targetId, "\n")] = 0;

        if (strlen(targetId) == 0) {
            printf("ID khong duoc de trong!\n");
            continue;
        }

        // Ki?m tra t?n t?i
        exist = 0;
        for (int i = 0; i < Account_size; i++) {
            if (strcmp(addAccounts[i].accountId, targetId) == 0) {
                exist = 1;
                break;
            }
        }

        if (!exist) {
            printf("Tai khoan khong ton tai!\n");
            continue;
        }

        break;
    }

    // --- L?c giao d?ch liên quan ---
    int found = 0;

    printf("\n===== LICH SU GIAO DICH CUA TAI KHOAN %s =====\n", targetId);
    printf("------------------------------------------------------------------------\n");
    printf("| %-4s | %-12s | %-10s | %-15s | %-15s |\n", 
           "STT", "Loai GD", "So tien", "Nguoi gui", "Nguoi nhan");
    printf("------------------------------------------------------------------------\n");

    for (int i = 0; i < transaction_size; i++) {
        if (strcmp(addTran[i].senderId, targetId) == 0 || strcmp(addTran[i].receiverId, targetId) == 0) {
            found++;
            char *direction = (strcmp(addTran[i].senderId, targetId) == 0) ? "Out" : "In";

            // L?y tên d?y d? ngu?i g?i và nh?n
            char senderName[50] = "", receiverName[50] = "";
            for (int j = 0; j < Account_size; j++) {
                if (strcmp(addAccounts[j].accountId, addTran[i].senderId) == 0) {
                    strcpy(senderName, addAccounts[j].fullName);
                }
                if (strcmp(addAccounts[j].accountId, addTran[i].receiverId) == 0) {
                    strcpy(receiverName, addAccounts[j].
					
					
					
					
					
					fullName);
                }
            }

            printf("| %-4d | %-12s | %-10.2lf | %-15s | %-15s |\n",
                   found,
                   direction,
                   addTran[i].amount,
                   senderName,
                   receiverName
            );
        }
    }

    printf("------------------------------------------------------------------------\n");

    if (!found) {
        printf(">>> He thong chua co giao dich nao!\n");
    }
}

int main (){
	int choice;
	do {
		printf ("\n________Quan Ly Ngan Hang_________\n");
		printf ("|     1.Them tai khoan moi.      |\n");
		printf ("|     2.Cap nhat thong tin.      |\n");
		printf ("|     3.Quan ly trang thai.      |\n");
		printf ("|     4.Tra cuu.                 |\n");
		printf ("|     5.Danh sach.               |\n");
		printf ("|     6.Sap xep danh sach.       |\n");
		printf ("|     7.Giao dich chuyen khoan.  |\n");
		printf ("|     8.Lich su giao dich.       |\n");
		printf ("|_____9.Thoat.___________________|\n");
		printf ("Moi ban nhap lua chon: ");
		if (  scanf (" %d",&choice) != 1){
			while (getchar() != '\n');
			printf ("Lua chon khong hop le.\n");
			continue;
		}
		
		switch (choice) {
			case 1:
				newAccount();
			break;
			
			case 2: 
				updateAccounts();
			break;
			
			case 3:
				manageStatus();
			break; 	
			
			case 4:
				 searchAccount();
			break;
			
			case 5:
				listAccounts(addAccounts, Account_size);
			break;
			
			case 6:
				sortAccounts(addAccounts, Account_size);
			break;
			
			case 7:
				Transactions();
			break;
			
			case 8:
				 viewTransactionHistory();
			break;	 
			
			case 9:
				printf ("Ket thuc chuong trinh !\n");
			break;
			
			default:
				printf ("Lua chon khong hop le. Vui long chon lai !");
			break;	
	}
	}while (choice != 9 );
	return 0;
}
	
