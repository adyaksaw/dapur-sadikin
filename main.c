#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/data_structure/data_type.h"
#include "lib/data_structure/gdt/game_data_type.h"
#include "lib/handler/handler_include.h"


#define initialX 4
#define initialY 4


GameState gameState;
Player player;
Queue CustomerQueue;
BinTree resep;

Second GameTime;

Object *ArrayOfMeja[13];

Item ArrayOfItem[30];

Matrix Map1, Map2, Map3, Kitchen;
Graph BIG_MAP;
adrNode Pn;
adrSuccNode Pt;


void SaveToFile(char *FileName){
    int i;

    FILE *save;
    Stack handtemp;
    save = fopen(FileName,"w");
    //Player Info
    printKataToFile(Name(player), save);
    fprintf(save,"\n");
    //fprintf(save,"%s\n",Name(player).TabKata);
    fprintf(save,"%f %f %d\n",Absis(player.pos),Ordinat(player.pos),player.currentRoom);
    fprintf(save,"%ld\n",Money(player));
    fprintf(save,"%d\n",Life(player));
    fprintf(save,"%d\n", GameTime);
    Save_Stack(&Hand(player),save);
    fprintf(save,"ES 0\n");
    Save_Stack(&Food(player),save);
    fprintf(save,"ES 0\n");

    //Customer Queue
    Save_Queue(CustomerQueue,save);
    fprintf(save,"0 0 0 0 0\n"); //0 Adalah "tanda" yang menandakan Berakhirnya Pembacaan Queue

    //Table
    for (i = 1; i<=12; i++){
        Object M = *ArrayOfMeja[i];
        if (!IsOccupied(M)){
            fprintf(save,"%d %d\n",TableNumber(M), IsOccupied(M));
        } else {
            fprintf(save,"%d %d %d %d %d %d %d\n",TableNumber(M), IsOccupied(M),Amount(CustomerAt(M)), OrdersAt(M),Patience(CustomerAt(M)), Priority(CustomerAt(M)),Status(CustomerAt(M)));
        }
    }
    fprintf(save,"EQ\n");
    //
    printf("Save Sukses\n");
    fclose(save);
}

void LoadFromFile(char *FileName){
    int i;

    FILE *load;
    Stack handtemp;
    if(isPointValid(player.pos) && ElmtMx(*(player.currentMap), (int) Absis(player.pos), (int) Ordinat(player.pos)).tag == PLAYER_POS){
        printf("1\n");
        SetTag_Matrix(player.currentMap, (int) Absis((player).pos), (int) Ordinat((player).pos), EMPTY);
    }
    load = fopen(FileName,"r");
    //Player Info
    char raw_input[10] = "";
    fscanf(load,"%s",raw_input);
    isiKata(&Name(player),raw_input,9);
    fscanf(load,"%f %f %d",&Absis(player.pos),&Ordinat(player.pos),&player.currentRoom);
    if(player.currentRoom == 1){
        *(player.currentMap) = Map1;
    } else if(player.currentRoom == 2){
        *(player.currentMap) = Map2;
    } else if(player.currentRoom == 3){
        *(player.currentMap) = Map3;
    } else {
        *(player.currentMap) = Kitchen;
    }
    SetTag_Matrix(player.currentMap, (int) Absis((player).pos), (int) Ordinat((player).pos), PLAYER_POS);
    fscanf(load,"%ld",&Money(player));
    fscanf(load,"%d",&Life(player));
    fscanf(load,"%d", &GameTime);
    Input_Stack(&Hand(player),load);
    Input_Stack(&Food(player),load);
    //Customer Queue
    Load_Queue(&CustomerQueue,load);
    printf("End Pembacaan Q\n");
    //Pembacaan berhenti saat pembacaan menemukan 0 sebagai nilai Amount,
    //Amount pastilah [1..4]

    //Table
    for (i = 1; i<=12; i++){
        //printf("Mantap");
        int NomerMeja;
        //TableNumber(*ArrayOfMeja[i])
        fscanf(load,"%d %d",&NomerMeja, &IsOccupied(*ArrayOfMeja[i]));
        printf("%d Mantap\n", NomerMeja);
        printf("%d", IsOccupied(*ArrayOfMeja[i]));
        if (IsOccupied(*ArrayOfMeja[i]) == 1){
            Customer *customer = malloc(sizeof(Customer));
            fscanf(load,"%d %d %d %d %d",&Amount(*customer), &FoodOrderID(*customer), &Patience(*customer), &Priority(*customer), &Status(*customer));

            TableNum(*customer) = TableNumber(*ArrayOfMeja[i]);
            printCustomer(*customer);

            (*ArrayOfMeja[i]).data.table.customer_here = customer;
            (*ArrayOfMeja[i]).data.table.isOccupied = true;
            printf("BINGITS\n");
        }
    }
    printf("Load Sukses\n");
    fclose(load);
}
void PrintAllOrder(){
    for (int i = 1; i <= 12; i++){
        if (IsOccupied(*(ArrayOfMeja[i]))){
            printf("Meja No.%d memesan OrderID %d.\n", i, OrdersAt(*(ArrayOfMeja[i])));
        }else {
            printf("Meja No.%d kosong.\n", i);
        }
    }
}

void PrintTableStatus(Object Meja){
    printf("Nomor Meja: %d\n", TableNumber(Meja));
    printf("IsOccupied: %d\n", IsOccupied(Meja));
    if (IsOccupied(Meja)){
        printf("Patience: %d\n", Patience(CustomerAt(Meja)));
        printf("Jumlah orang: %d\n", Amount(CustomerAt(Meja)));
        printCustomer(CustomerAt(Meja));
    }
}

void PrintAllMemory(Matrix * M){
    for (int i = 1; i <= 8; i++){
        for (int j = 1; j <= 8; j++){
            printf("ALAMAT MEMORY M KE %d-%d adalah %p.\n", i, j, &((*M).Mem[i][j]));
        }
    }
}

void PrintAllTable(){
    for (int i = 1; i <= 12; i++){
        PrintTableStatus(*(ArrayOfMeja[i]));
    }
}

void Dealokasi_All_Meja(){
    for (int i = 1; i <= 12; i++){
        if (IsOccupied(*(ArrayOfMeja[i]))){
            Dealokasi_Customer((*(ArrayOfMeja[i])).data.table.customer_here);
        }
    }
}

void Init(){
    CreateBigMap(&Map1,&Map2,&Map3,&Kitchen,&BIG_MAP);
    int i;
    srand(time(NULL));
    Create_New_Player(&player);
    LoadMap(&Map1, &Map2, &Map3, &Kitchen);

    FILE *fp;
    fp = fopen(NamaFile3, "r");
    if (fp == NULL)
        printf("File tidak terdeteksi\n");
    resep = BuildBalanceTree(23,fp);

    for(i = 1; i <= 23; i++){
        ArrayOfItem[i] = SearchItemTree(resep, i);
        printf("Nama item ke %d: ",i);
        printKata((ArrayOfItem[i].name));
        printf(" %d\n", ItemID(ArrayOfItem[i]));
    }

    GameTime = 0;
    printf("Init\n");
    //PrintAllMemory(&Map1);
    /*
        Melakukan inisialisasi dari array of pointer ArrayOfMeja.
        ArrayOfMeja akan berisi pointer menuju semua objek meja sesuai nomornya.
        Sebagai contoh, ketika diakses *(ArrayOfMeja[3]) maka akan diakses
        memori yang menyimpan objek yang merupakan meja dengan nomor meja 3.
    */
    for (int i = 1; i <= 8; i++){
        for (int j = 1; j <= 8; j++){
            if (ElmtMx(Map1, i, j).tag == TABLE){
                ArrayOfMeja[ElmtMx(Map1, i, j).data.table.num] = &(ElmtMx(Map1, i, j));
            }
        }
    }

    for (int i = 1; i <= 8; i++){
        for (int j = 1; j <= 8; j++){
            if (ElmtMx(Map1, i, j).tag == TABLE){
                ArrayOfMeja[ElmtMx(Map2, i, j).data.table.num] = &(ElmtMx(Map2, i, j));
            }
        }
    }

    for (int i = 1; i <= 8; i++){
        for (int j = 1; j <= 8; j++){
            if (ElmtMx(Map1, i, j).tag == TABLE){
                ArrayOfMeja[ElmtMx(Map3, i, j).data.table.num] = &(ElmtMx(Map3, i, j));
            }
        }
    }

    player.currentMap = &Map1;
    player.currentRoom = 1;

    Absis(player.pos) = initialX;
    Ordinat(player.pos) = initialY;

    SetTag_Matrix(player.currentMap, initialX, initialY, PLAYER_POS);
}

void CustomerGenerator(){
    float customerAppearChance = 100*(1-sqrt(1.0/GameTime));
    if (!IsFull_Queue(CustomerQueue) && (rand()%100) + 1 <= customerAppearChance){
        Customer *newCustomer;
        newCustomer = GenerateCustomer();

        printf("New Customer\n");
        printCustomer(*newCustomer);

        Add_Queue(&CustomerQueue, newCustomer);
    }
}

void reduceAllCustPatience(){
    int i;
    ElType_Queue temp;
    Customer * X;

    if(!IsEmpty_Queue(CustomerQueue)){
        if(!IsFull_Queue(CustomerQueue)){
            for(i = Head(CustomerQueue); i != 1+(Tail(CustomerQueue)%MaxEl(CustomerQueue)); i = 1+(i%MaxEl(CustomerQueue))){
                Reduce_Patience(CustomerQueue.T[i]);
                if(Patience(*(CustomerQueue.T[i])) == 0){
                    printf("Terlalu lama menunggu, ada pelanggan di antrian yang bosan dan memilih makan di geprek.\n");
                    normalizedQueue(&CustomerQueue, i);
                    RemoveCustomerFromTable(ArrayOfMeja[i]);
                    Reduce_Life(&player);
                }
            }
        } else {
            for(i = 1; i <= MaxEl(CustomerQueue); i++){
                Reduce_Patience(CustomerQueue.T[i]);
                if(Patience(*(CustomerQueue.T[i])) == 0){
                    printf("Terlalu lama menunggu, ada pelanggan di antrian yang bosan dan memilih makan di geprek.\n");
                    normalizedQueue(&CustomerQueue, i);
                    RemoveCustomerFromTable(ArrayOfMeja[i]);
                    Reduce_Life(&player);
                }
            }
        }
    }
    for(i = 1; i <= 12; i++){
        if((*ArrayOfMeja[i]).data.table.isOccupied){
            Customer * Cust = (*ArrayOfMeja[i]).data.table.customer_here;
            Reduce_Patience(Cust);
            if(Patience(*Cust) == 0){
                printf("Terlalu lama menunggu, pelanggan di meja %d bosan dan memilih makan di geprek.\n", i);
                RemoveCustomerFromTable(ArrayOfMeja[i]);
                Reduce_Life(&player);
            }
        }
    }
}

void CheckTransitiontoGraph (Matrix *M1, Matrix *M2, Direction dir) {

  Pt = SearchEdge(BIG_MAP,player.currentMap,M1);
  if (Pt != Nil) {
    if(Dir(Pt) == dir) {
      if((Ordinat(Transition(Pt)) == Ordinat(player.pos)) && (Absis(Transition(Pt)) == Absis(player.pos))) {

        SetTag_Matrix(player.currentMap, (int) Absis((player).pos), (int) Ordinat((player).pos), EMPTY);
        player.pos = Spawn(Pt);
        player.currentMap = Id(Succ(Pt));
        SetTag_Matrix(player.currentMap, (int)(Absis(Spawn(Pt))), (int)(Ordinat(Spawn(Pt))), PLAYER_POS);
        player.currentRoom = RoomID(*player.currentMap);
        reduceAllCustPatience();
        CustomerGenerator(&CustomerQueue);
        UpdateTime(&GameTime);
      } else {
        Move_Player_Direction(player.currentMap, &player, dir);
        reduceAllCustPatience();
        CustomerGenerator(&CustomerQueue);
        UpdateTime(&GameTime);
      }
    } else {
      Move_Player_Direction(player.currentMap, &player, dir);
      reduceAllCustPatience();
      CustomerGenerator(&CustomerQueue);
      UpdateTime(&GameTime);
    }
  } else {
    Pt = SearchEdge(BIG_MAP,player.currentMap,M2);
    if (Pt != Nil) {
      if(Dir(Pt) == dir) {
        if((Ordinat(Transition(Pt)) == Ordinat(player.pos)) && (Absis(Transition(Pt)) == Absis(player.pos))) {

          SetTag_Matrix(player.currentMap, (int) Absis((player).pos), (int) Ordinat((player).pos), EMPTY);
          player.pos = Spawn(Pt);
          player.currentMap = Id(Succ(Pt));
          SetTag_Matrix(player.currentMap, (int)(Absis(Spawn(Pt))), (int)(Ordinat(Spawn(Pt))), PLAYER_POS);
          player.currentRoom = RoomID(*player.currentMap);
          reduceAllCustPatience();
          CustomerGenerator(&CustomerQueue);
          UpdateTime(&GameTime);
        } else {
          Move_Player_Direction(player.currentMap, &player, dir);
          reduceAllCustPatience();
          CustomerGenerator(&CustomerQueue);
          UpdateTime(&GameTime);
        }
      } else {
        Move_Player_Direction(player.currentMap, &player, dir);
        reduceAllCustPatience();
        CustomerGenerator(&CustomerQueue);
        UpdateTime(&GameTime);
      }
  } else {
    Move_Player_Direction(player.currentMap, &player, dir);
    reduceAllCustPatience();
    CustomerGenerator(&CustomerQueue);
    UpdateTime(&GameTime);
  }
}

}

void InputProcessor(char input[], int input_length){
    Kata processedInput;
    isiKata(&processedInput, input, input_length);

    Kata quitInput;
    isiKata(&quitInput, "quit", 4);

    Kata statusInput;
    isiKata(&statusInput, "status", 6);

    Kata moveInputUp;
    isiKata(&moveInputUp, "GU", 2);

    Kata moveInputDown;
    isiKata(&moveInputDown, "GD", 2);

    Kata moveInputLeft;
    isiKata(&moveInputLeft, "GL", 2);

    Kata moveInputRight;
    isiKata(&moveInputRight, "GR", 2);

    Kata queueInput;
    isiKata(&queueInput, "queue", 5);

    Kata allOrderInput;
    isiKata(&allOrderInput, "allOrder", 8);

    Kata placeInput;
    isiKata(&placeInput, "place", 5);

    Kata checkInput;
    isiKata(&checkInput, "check", 5);

    Kata memoryInput;
    isiKata(&memoryInput, "memcheck", 8);

    Kata helpInput;
    isiKata(&helpInput, "help", 4);

    Kata orderInput;
    isiKata(&orderInput, "order", 5);

    Kata tableInput;
    isiKata(&tableInput, "printMeja", 10);

    Kata tanganInput;
    isiKata(&tanganInput, "hand", 4);

    Kata buangTanganInput;
    isiKata(&buangTanganInput, "CH", 2);

    Kata nampanInput;
    isiKata(&nampanInput, "tray", 4);

    Kata buangNampanInput;
    isiKata(&buangNampanInput, "CT", 2);

    Kata giveInput;
    isiKata(&giveInput, "give", 4);

    Kata removeCustInput;
    isiKata(&removeCustInput, "remove", 6);

    Kata teleportDapurInput;
    isiKata(&teleportDapurInput, "kitchen", 7);

    Kata teleportMap1Input;
    isiKata(&teleportMap1Input, "Map1", 4);

    Kata takeInput;
    isiKata(&takeInput, "take", 4);

    Kata putInput;
    isiKata(&putInput, "put", 3);

    Kata recipeInput;
    isiKata(&recipeInput, "recipe",6);

    Kata saveInput;
    isiKata(&saveInput , "save",4);

    Kata loadInput;
    isiKata(&loadInput, "load",4);

    if (IsKataSama(processedInput, quitInput)){ //COMMAND quit
        gameState = CREDITS;
    }else if (IsKataSama(processedInput, statusInput)){ //COMMAND status
        Print_Player(player);
    }else if (IsKataSama(processedInput, moveInputUp)){ //COMMAND GU
      CheckTransitiontoGraph (&Map1, &Map2, UP);
    }else if (IsKataSama(processedInput, moveInputDown)){ //COMMAND GD
      CheckTransitiontoGraph (&Kitchen, &Map3, DOWN);
    }else if (IsKataSama(processedInput, moveInputLeft)){ //COMMAND GL
      CheckTransitiontoGraph (&Kitchen, &Map1, LEFT);
    }else if (IsKataSama(processedInput, moveInputRight)){ //COMMAND GR
      CheckTransitiontoGraph (&Map2, &Map3, RIGHT);
    }else if (IsKataSama(processedInput, queueInput)){ //COMMAND queue
        Print_Queue(CustomerQueue);
    }else if (IsKataSama(processedInput, allOrderInput)){ //COMMAND allOrder
        PrintAllOrder();
    }else if (IsKataSama(processedInput, checkInput)){ //COMMAND check
        Object * ClosestTable = Closest_Empty_Table(player, (player.currentMap));
    }else if (IsKataSama(processedInput, memoryInput)){ //COMMAND memcheck
        PrintAllMemory(player.currentMap);
    }else if (IsKataSama(processedInput, tableInput)){ //COMMAND printMeja
        PrintAllTable();
    }else if (IsKataSama(processedInput, tanganInput)){ //COMMAND hand
        PrintData_Stack(player.hand, 1);
    }else if (IsKataSama(processedInput, buangTanganInput)){ //COMMAND CH
        CreateEmpty_Stack(&(player.hand));
    }else if (IsKataSama(processedInput, nampanInput)){ //COMMAND tray
        PrintData_Stack(player.food, 0);
    }else if (IsKataSama(processedInput, buangNampanInput)){ //COMMAND CH
        CreateEmpty_Stack(&(player.food));
    }else if (IsKataSama(processedInput, putInput)){ //COMMAND CH
        Object * Closest_Tray = Closest_Object(player, player.currentMap, TRAY);
        if(Closest_Tray != NULL){
            Masak(&player, resep);
        } else {
            printf("Tidak ada nampan disekitarmu!\n");
        }

    }else if (IsKataSama(processedInput, orderInput)){ //COMMAND order
        Object * ClosestTable = Closest_Table(player, (player.currentMap));
        if (ClosestTable != NULL){
            if (IsOccupied(*ClosestTable)){
                if(!hasOrdered((*ClosestTable).data.table.customer_here)){
                    GenerateOrder((*ClosestTable).data.table.customer_here);
                    printf("Pesanan di meja nomor %d adalah FoodID %d, yaitu ", TableNumber(*ClosestTable), OrdersAt(*ClosestTable));
                    printKata(ArrayOfItem[OrdersAt(*ClosestTable)].name);
                    printf(".\n");
                } else {
                    printf("Customer pada meja %d telah memesan FoodID %d, yaitu ", TableNumber(*ClosestTable), OrdersAt(*ClosestTable));
                    printKata(ArrayOfItem[OrdersAt(*ClosestTable)].name);
                }
            } else {
                printf("Meja nomor %d kosong.\n", TableNumber(*ClosestTable));
            }
        }else {
            printf("Tidak ada meja kosong disekitarmu!\n");
        }
    }else if (IsKataSama(processedInput, placeInput)){ //COMMAND place
        Object * ClosestTable = Closest_Empty_Table(player, (player.currentMap));
        if (ClosestTable != NULL){
            printf("Meja dengan nomor %d kosong.\n", (*ClosestTable).data.table.num);
            if (!IsEmpty_Queue(CustomerQueue)){
                Customer * CustomerToPlace = InfoHead(CustomerQueue);
                boolean successfulPlace = PlaceCustomerToTable(ClosestTable, CustomerToPlace);
                if (successfulPlace){
                    Del_Queue(&CustomerQueue, &CustomerToPlace);
                } else {
                    successfulPlace = findValidCust(ClosestTable, &CustomerQueue);
                    if(!successfulPlace){
                        printf("Tidak ada customer yang valid untuk meja ini\n");
                    }
                }
                if (IsOccupied(*ClosestTable)){
                    printf("Sekarang meja nomor %d sudah diduduki.\n", TableNumber(*ClosestTable));
                }
            } else {
                printf("Antrian kosong.\n");
            }
        }else {
            printf("Tidak ada meja kosong disekitarmu!\n");
        }
    } else if(IsKataSama(processedInput, helpInput)){ //COMMAND help
        printf("Ketik help untuk melihat daftar command.\n");
        printf("Ketik GU untuk memindahkan player ke atas.\n");
        printf("Ketik GD untuk memindahkan player ke bawah.\n");
        printf("Ketik GL untuk memindahkan player ke kiri.\n");
        printf("Ketik GR untuk memindahkan player ke kanan.\n");
        printf("Ketik allOrder untuk melihat order untuk setiap meja.\n");
        printf("Ketik queue untuk melihat antrian saat ini\n");
        printf("Ketik status untuk melihat status pemain\n");
        printf("Ketik place untuk menaruh customer di meja sekitar");
        printf("Ketik give untuk memberikan makanan dari food tray ke customer.\n");
        printf("Ketik take untuk mengambil makanan dari kompor ke tangan.\n");
        printf("Ketik recipe untuk melihat resep yang ada.\n");
    } else if(IsKataSama(processedInput, giveInput)){ //COMMAND give
        Object * ClosestTable = Closest_Table(player, (player.currentMap));
        if(ClosestTable != NULL){
            if((*ClosestTable).data.table.isOccupied){
                Customer * Cust = (*ClosestTable).data.table.customer_here;
                if(FoodOrderID(*Cust) == ItemID(InfoTop(player.food))){
                    Money(player) += FoodPrice*(1+(Patience(*Cust)+Priority(*Cust)+Amount(*Cust))/FoodPriceModifier);
                    printf("Pelanggan tersebut puas dengan makanannya!\n");
                    printf("Kamu mendapatkan %d\n", FoodPrice*(1+(Patience(*Cust)+Priority(*Cust)+Amount(*Cust))/FoodPriceModifier));
                    RemoveCustomerFromTable(ClosestTable);
                } else if(IsEmpty_Stack(player.food)){
                    printf("Nampan kosong\n");
                } else {
                    printf("Makanan di nampan paling atas tidak sesuai dengan keinginan customer ini\n");
                }
            } else {
                printf("Tidak ada customer di meja tersebut\n");
            }
        } else {
            printf("Tidak ada meja disekitarmu\n");
        }
    } else if(IsKataSama(processedInput, removeCustInput)){ //COMMAND debug: remove
        Object * ClosestTable = Closest_Table(player, (player.currentMap));
        RemoveCustomerFromTable(ClosestTable);
    } else if(IsKataSama(processedInput, takeInput)){ // COMMAND take
        Object * Closest_Stove = Closest_Object(player, player.currentMap, STOVE);
        if(Closest_Stove != NULL){

            printf("Kamu mengambil ItemID %d dari kompor, yaitu: ", (*Closest_Stove).data.stove.itemID);
            printKata((ArrayOfItem[(*Closest_Stove).data.stove.itemID].name));
            Push_Stack(&player.hand, ArrayOfItem[(*Closest_Stove).data.stove.itemID]);
        } else {
            printf("Tidak ada kompor di sekitar player\n");
        }
    } else if (IsKataSama(processedInput,recipeInput)) { // COMMAND recipe
        printf("Berikut adalah resep makanan di game ini!\n\n");
        PrintTree(resep,3);
        printf("\n");
    } else if (IsKataSama(processedInput, loadInput)){
      LoadFromFile("save.txt");
    } else if (IsKataSama(processedInput,saveInput)) {
      SaveToFile("Save.txt");
    }
}

void MainScreen(){
    printf("Main Screen\n");
    char rawInput[10] = "";
    while (gameState == MAIN_MENU){
        Create_New_Player(&player);
        printf("Welcome to Dapur Sadikin!\n");
        printf("What is your name?\n");
        printf("Name : ");
        scanf("%s", &rawInput);
        Set_Player_Name(&player, rawInput, 10);
        printf("Selamat datang, ");
        printKata(player.name);
        printf(".\n");
        gameState = IN_GAME;
    }
}

void MainGame(){
    printf("Main Game\n");
    //PrintAllMemory(Map1);

    char rawInput[10] = "";

    CreateEmpty_Queue(&CustomerQueue, 5);

    while (gameState == IN_GAME){
        /*
        printf("Map 1\n");
        Print_Room(Map1);
        printf("Map 2\n");
        Print_Room(Map2);
        printf("Map 3\n");
        Print_Room(Map3);
        printf("Dapur\n");
        Print_Kitchen(Kitchen);
        */
        printf("Input : ");
        scanf("%s", &rawInput);
        InputProcessor(rawInput, 10);
        Print_Room(*(player.currentMap));
        if(Life(player) <= 0){
            printf("Dikarenakan banyak pelanggan yang tidak puas, akhirnya terjadi demo, dan restoranmu disegel oleh negara.\n");
            printf("GAME OVER!\n");
            gameState = CREDITS;
        }
    }
    DeAlokasi_Queue(&CustomerQueue);
    Dealokasi_All_Meja();
}

int main(){
    Init();
    printf("After init\n");
    //PrintAllMemory(Map1);
    printf("After init2\n");
    //PrintAllMemory(Map1);

    gameState = MAIN_MENU;
    printf("%d\n", gameState);

    MainScreen();
    //printf("Player pos : %f %f",Absis(player.pos),Ordinat(player.pos));
    //printf("After mainscreen\n");
    //PrintAllMemory(Map1);
    //printf("After mainscreen2\n");
    //printf("Player pos : %f %f",Absis(player.pos),Ordinat(player.pos));
    //PrintAllMemory(Map1);

    MainGame();

    gameState = CREDITS;
    printf("%d\n", gameState);

    printf("Before quit\n");
    //PrintAllMemory(Map1);
    printf("Before quit2\n");
    //PrintAllMemory(Map1);
}
