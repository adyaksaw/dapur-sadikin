#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "session.h"
#include <ncurses.h>

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

void SaveToFile(char *FileName)
{
    int i;

    FILE *save;
    Stack handtemp;
    save = fopen(FileName, "w");
    //Player Info
    fprintw(save, "%s", Name(player));
    fprintw(save, "%d %d", Absis(player.pos), Ordinat(player.pos));
    fprintw(save, "%ld", Money(player));
    fprintw(save, "%d", Life(player));
    fprintw(save, "%d", GameTime);
    Save_Stack(&Hand(player), save);
    fprintw(save, "ES");
    Save_Stack(&Food(player), save);
    fprintw(save, "ES");

    //Customer Queue
    Save_Queue(CustomerQueue, save);
    fprintw(save, "0"); //0 Adalah "tanda" yang menandakan Berakhirnya Pembacaan Queue

    //Table
    for (i = 1; i <= 12; i++)
    {
        Object M = *ArrayOfMeja[i];
        if (!IsOccupied(M))
        {
            fprintw(save, "%d %d", TableNumber(M), IsOccupied(M));
        }
        else
        {
            fprintw(save, "%d %d %d %d %d %d", TableNumber(M), IsOccupied(M), Amount(CustomerAt(M)), OrdersAt(M), Patience(CustomerAt(M)), Priority(CustomerAt(M)));
        }
    }
    fprintw(save, "EQ");
    //
    fclose(save);
}

void LoadFromFile(char *FileName)
{
    int i;

    FILE *load;
    Stack handtemp;
    load = fopen(FileName, "r");
    //Player Info
    fscanf(load, "%s", &Name(player));
    fscanf(load, "%d %d", &Absis(player.pos), &Ordinat(player.pos));
    fscanf(load, "%ld", &Money(player));
    fscanf(load, "%d", &Life(player));
    fscanf(load, "%d", &GameTime);
    Input_Stack(&Hand(player), load);
    Input_Stack(&Food(player), load);

    //Customer Queue
    Load_Queue(&CustomerQueue, load);
    //Pembacaan berhenti saat pembacaan menemukan 0 sebagai nilai Amount,
    //Amount pastilah [1..4]

    //Table
    for (i = 1; i <= 12; i++)
    {
        Object M = *ArrayOfMeja[i];
        fscanf(load, "%d %d", &TableNumber(M), &IsOccupied(M));
        if (IsOccupied(M))
        {
            fscanf(load, "%d %d %d %d", &Amount(CustomerAt(M)), &OrdersAt(M), &Patience(CustomerAt(M)), &Priority(CustomerAt(M)));
            TableNum(CustomerAt(M)) = TableNumber(M);
        }
    }
    fclose(load);
}
void PrintAllOrder()
{
    for (int i = 1; i <= 12; i++)
    {
        if (IsOccupied(*(ArrayOfMeja[i])))
        {
            printw("Meja No.%d memesan OrderID %d.\n", i, OrdersAt(*(ArrayOfMeja[i])));
        }
        else
        {
            printw("Meja No.%d kosong.\n", i);
        }
    }
}

void PrintTableStatus(Object Meja)
{
    printw("Nomor Meja: %d\n", TableNumber(Meja));
    printw("IsOccupied: %d\n", IsOccupied(Meja));
    if (IsOccupied(Meja))
    {
        printw("Patience: %d\n", Patience(CustomerAt(Meja)));
        printw("Jumlah orang: %d\n", Amount(CustomerAt(Meja)));
        printCustomer(CustomerAt(Meja));
    }
}

void PrintAllMemory(Matrix *M)
{
    for (int i = 1; i <= 8; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            printw("ALAMAT MEMORY M KE %d-%d adalah %p.\n", i, j, &((*M).Mem[i][j]));
        }
    }
}

void PrintAllTable()
{
    for (int i = 1; i <= 12; i++)
    {
        PrintTableStatus(*(ArrayOfMeja[i]));
    }
}

void Dealokasi_All_Meja()
{
    for (int i = 1; i <= 12; i++)
    {
        if (IsOccupied(*(ArrayOfMeja[i])))
        {
            Dealokasi_Customer((*(ArrayOfMeja[i])).data.table.customer_here);
        }
    }
}

void Init()
{
    CreateBigMap(&Map1, &Map2, &Map3, &Kitchen, &BIG_MAP);
    int i;
    srand(time(NULL));

    for (i = 0; i <= 29; i++)
    {
        ItemID(ArrayOfItem[i]) = 0;
        isiKata(&(ArrayOfItem[i].name), "Test_food", 9);
    }
    Create_New_Player(&player);
    LoadMap(&Map1, &Map2, &Map3, &Kitchen);

    GameTime = 0;
    printw("Init\n");
    //PrintAllMemory(&Map1);

    resep = NULL;

    /*
        Melakukan inisialisasi dari array of pointer ArrayOfMeja.
        ArrayOfMeja akan berisi pointer menuju semua objek meja sesuai nomornya.
        Sebagai contoh, ketika diakses *(ArrayOfMeja[3]) maka akan diakses
        memori yang menyimpan objek yang merupakan meja dengan nomor meja 3.
    */
    for (int i = 1; i <= 8; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            if (ElmtMx(Map1, i, j).tag == TABLE)
            {
                ArrayOfMeja[ElmtMx(Map1, i, j).data.table.num] = &(ElmtMx(Map1, i, j));
            }
        }
    }

    for (int i = 1; i <= 8; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            if (ElmtMx(Map1, i, j).tag == TABLE)
            {
                ArrayOfMeja[ElmtMx(Map2, i, j).data.table.num] = &(ElmtMx(Map2, i, j));
            }
        }
    }

    for (int i = 1; i <= 8; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            if (ElmtMx(Map1, i, j).tag == TABLE)
            {
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

void CustomerGenerator()
{
    if (!IsFull_Queue(CustomerQueue))
    {
        Customer *newCustomer;
        newCustomer = GenerateCustomer();

        printw("New Customer\n");
        printCustomer(*newCustomer);

        Add_Queue(&CustomerQueue, newCustomer);
    }
}

void reduceAllCustPatience()
{
    int i;
    ElType_Queue temp;
    Customer *X;

    if (!IsEmpty_Queue(CustomerQueue))
    {
        if (!IsFull_Queue(CustomerQueue))
        {
            for (i = Head(CustomerQueue); i != 1 + (Tail(CustomerQueue) % MaxEl(CustomerQueue)); i = 1 + (i % MaxEl(CustomerQueue)))
            {
                Reduce_Patience(CustomerQueue.T[i]);
                if (Patience(*(CustomerQueue.T[i])) == 0)
                {
                    printw("Terlalu lama menunggu, ada pelanggan di antrian yang bosan dan memilih makan di geprek.\n");
                    normalizedQueue(&CustomerQueue, i);
                    RemoveCustomerFromTable(ArrayOfMeja[i]);
                    Reduce_Life(&player);
                }
            }
        }
        else
        {
            for (i = 1; i <= MaxEl(CustomerQueue); i++)
            {
                Reduce_Patience(CustomerQueue.T[i]);
                if (Patience(*(CustomerQueue.T[i])) == 0)
                {
                    printw("Terlalu lama menunggu, ada pelanggan di antrian yang bosan dan memilih makan di geprek.\n");
                    normalizedQueue(&CustomerQueue, i);
                    RemoveCustomerFromTable(ArrayOfMeja[i]);
                    Reduce_Life(&player);
                }
            }
        }
    }
    for (i = 1; i <= 12; i++)
    {
        if ((*ArrayOfMeja[i]).data.table.isOccupied)
        {
            Customer *Cust = (*ArrayOfMeja[i]).data.table.customer_here;
            Reduce_Patience(Cust);
            if (Patience(*Cust) == 0)
            {
                printw("Terlalu lama menunggu, pelanggan di meja %d bosan dan memilih makan di geprek.\n", i);
                RemoveCustomerFromTable(ArrayOfMeja[i]);
                Reduce_Life(&player);
            }
        }
    }
}

void CheckTransitiontoGraph(Matrix *M1, Matrix *M2, Direction dir)
{

    Pt = SearchEdge(BIG_MAP, player.currentMap, M1);
    if (Pt != Nil)
    {
        if (Dir(Pt) == dir)
        {
            if ((Ordinat(Transition(Pt)) == Ordinat(player.pos)) && (Absis(Transition(Pt)) == Absis(player.pos)))
            {

                SetTag_Matrix(player.currentMap, (int)Absis((player).pos), (int)Ordinat((player).pos), EMPTY);
                player.pos = Spawn(Pt);
                player.currentMap = Id(Succ(Pt));
                SetTag_Matrix(player.currentMap, (int)(Absis(Spawn(Pt))), (int)(Ordinat(Spawn(Pt))), PLAYER_POS);
                player.currentRoom = RoomID(*player.currentMap);
                reduceAllCustPatience();
                CustomerGenerator(&CustomerQueue);
                UpdateTime(&GameTime);
            }
            else
            {
                Move_Player_Direction(player.currentMap, &player, dir);
                reduceAllCustPatience();
                CustomerGenerator(&CustomerQueue);
                UpdateTime(&GameTime);
            }
        }
        else
        {
            Move_Player_Direction(player.currentMap, &player, dir);
            reduceAllCustPatience();
            CustomerGenerator(&CustomerQueue);
            UpdateTime(&GameTime);
        }
    }
    else
    {
        Pt = SearchEdge(BIG_MAP, player.currentMap, M2);
        if (Pt != Nil)
        {
            if (Dir(Pt) == dir)
            {
                if ((Ordinat(Transition(Pt)) == Ordinat(player.pos)) && (Absis(Transition(Pt)) == Absis(player.pos)))
                {

                    SetTag_Matrix(player.currentMap, (int)Absis((player).pos), (int)Ordinat((player).pos), EMPTY);
                    player.pos = Spawn(Pt);
                    player.currentMap = Id(Succ(Pt));
                    SetTag_Matrix(player.currentMap, (int)(Absis(Spawn(Pt))), (int)(Ordinat(Spawn(Pt))), PLAYER_POS);
                    player.currentRoom = RoomID(*player.currentMap);
                    reduceAllCustPatience();
                    CustomerGenerator(&CustomerQueue);
                    UpdateTime(&GameTime);
                }
                else
                {
                    Move_Player_Direction(player.currentMap, &player, dir);
                    reduceAllCustPatience();
                    CustomerGenerator(&CustomerQueue);
                    UpdateTime(&GameTime);
                }
            }
            else
            {
                Move_Player_Direction(player.currentMap, &player, dir);
                reduceAllCustPatience();
                CustomerGenerator(&CustomerQueue);
                UpdateTime(&GameTime);
            }
        }
        else
        {
            Move_Player_Direction(player.currentMap, &player, dir);
            reduceAllCustPatience();
            CustomerGenerator(&CustomerQueue);
            UpdateTime(&GameTime);
        }
    }
}

void InputProcessor(char input[], int input_length)
{
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
    isiKata(&recipeInput, "recipe", 6);

    if (IsKataSama(processedInput, quitInput))
    { //COMMAND quit
        gameState = CREDITS;
    }
    else if (IsKataSama(processedInput, statusInput))
    { //COMMAND status
        Print_Player(player);
    }
    else if (IsKataSama(processedInput, moveInputUp))
    { //COMMAND GU
        CheckTransitiontoGraph(&Map1, &Map2, UP);
    }
    else if (IsKataSama(processedInput, moveInputDown))
    { //COMMAND GD
        CheckTransitiontoGraph(&Kitchen, &Map3, DOWN);
    }
    else if (IsKataSama(processedInput, moveInputLeft))
    { //COMMAND GL
        CheckTransitiontoGraph(&Kitchen, &Map1, LEFT);
    }
    else if (IsKataSama(processedInput, moveInputRight))
    { //COMMAND GR
        CheckTransitiontoGraph(&Map2, &Map3, RIGHT);
    }
    else if (IsKataSama(processedInput, queueInput))
    { //COMMAND queue
        Print_Queue(CustomerQueue);
    }
    else if (IsKataSama(processedInput, allOrderInput))
    { //COMMAND allOrder
        PrintAllOrder();
    }
    else if (IsKataSama(processedInput, checkInput))
    { //COMMAND check
        Object *ClosestTable = Closest_Empty_Table(player, (player.currentMap));
    }
    else if (IsKataSama(processedInput, memoryInput))
    { //COMMAND memcheck
        PrintAllMemory(player.currentMap);
    }
    else if (IsKataSama(processedInput, tableInput))
    { //COMMAND printMeja
        PrintAllTable();
    }
    else if (IsKataSama(processedInput, tanganInput))
    { //COMMAND hand
        PrintData_Stack(player.hand);
    }
    else if (IsKataSama(processedInput, buangTanganInput))
    { //COMMAND CH
        CreateEmpty_Stack(&(player.hand));
    }
    else if (IsKataSama(processedInput, nampanInput))
    { //COMMAND tray
        PrintData_Stack(player.food);
    }
    else if (IsKataSama(processedInput, buangNampanInput))
    { //COMMAND CH
        CreateEmpty_Stack(&(player.food));
    }
    else if (IsKataSama(processedInput, putInput))
    { //COMMAND CH
        Masak(&player, resep);
    }
    else if (IsKataSama(processedInput, orderInput))
    { //COMMAND order
        Object *ClosestTable = Closest_Table(player, (player.currentMap));
        if (ClosestTable != NULL)
        {
            if (IsOccupied(*ClosestTable))
            {
                if (!hasOrdered((*ClosestTable).data.table.customer_here))
                {
                    GenerateOrder((*ClosestTable).data.table.customer_here);
                    printw("Pesanan di meja nomor %d adalah FoodID %d.\n", TableNumber(*ClosestTable), OrdersAt(*ClosestTable));
                }
                else
                {
                    printw("Customer pada meja %d telah memesan FoodID %d sebelumnya\n", TableNumber(*ClosestTable), OrdersAt(*ClosestTable));
                }
            }
            else
            {
                printw("Meja nomor %d kosong.\n", TableNumber(*ClosestTable));
            }
        }
        else
        {
            printw("Tidak ada meja kosong disekitarmu!\n");
        }
    }
    else if (IsKataSama(processedInput, placeInput))
    { //COMMAND place
        Object *ClosestTable = Closest_Empty_Table(player, (player.currentMap));
        if (ClosestTable != NULL)
        {
            printw("Meja dengan nomor %d kosong.\n", (*ClosestTable).data.table.num);
            if (!IsEmpty_Queue(CustomerQueue))
            {
                Customer *CustomerToPlace = InfoHead(CustomerQueue);
                boolean successfulPlace = PlaceCustomerToTable(ClosestTable, CustomerToPlace);
                if (successfulPlace)
                {
                    Del_Queue(&CustomerQueue, &CustomerToPlace);
                }
                else
                {
                    successfulPlace = findValidCust(ClosestTable, &CustomerQueue);
                    if (!successfulPlace)
                    {
                        printw("Tidak ada customer yang valid untuk meja ini\n");
                    }
                }
                if (IsOccupied(*ClosestTable))
                {
                    printw("Sekarang meja nomor %d sudah diduduki.\n", TableNumber(*ClosestTable));
                }
            }
            else
            {
                printw("Antrian kosong.\n");
            }
        }
        else
        {
            printw("Tidak ada meja kosong disekitarmu!\n");
        }
    }
    else if (IsKataSama(processedInput, helpInput))
    { //COMMAND help
        printw("Ketik help untuk melihat daftar command.\n");
        printw("Ketik GU untuk memindahkan player ke atas.\n");
        printw("Ketik GD untuk memindahkan player ke bawah.\n");
        printw("Ketik GL untuk memindahkan player ke kiri.\n");
        printw("Ketik GR untuk memindahkan player ke kanan.\n");
        printw("Ketik allOrder untuk melihat order untuk setiap meja.\n");
        printw("Ketik queue untuk melihat antrian saat ini\n");
        printw("Ketik status untuk melihat status pemain\n");
        printw("Ketik place untuk mengecek petak sekitar");
        printw("Ketik quit untuk keluar dari permainan.\n");
    }
    else if (IsKataSama(processedInput, giveInput))
    { //COMMAND give
        Object *ClosestTable = Closest_Table(player, (player.currentMap));
        if (ClosestTable != NULL)
        {
            if ((*ClosestTable).data.table.isOccupied)
            {
                Customer *Cust = (*ClosestTable).data.table.customer_here;
                if (FoodOrderID(*Cust) == ItemID(InfoTop(player.food)))
                {
                    Money(player) += FoodPrice * (Patience(*Cust) / FoodPriceModifier);
                    printw("Pelanggan tersebut puas dengan makanannya!\n");
                    printw("Kamu mendapatkan %d\n", printw("Pelanggan tersebut puas dengan makanan", FoodPrice * (Patience(*Cust) / FoodPriceModifier)));
                    RemoveCustomerFromTable(ClosestTable);
                }
                else if (IsEmpty_Stack(player.food))
                {
                    printw("Nampan kosong\n");
                }
                else
                {
                    printw("Makanan di nampan paling atas tidak sesuai dengan keinginan customer ini\n");
                }
            }
            else
            {
                printw("Tidak ada customer di meja tersebut\n");
            }
        }
        else
        {
            printw("Tidak ada meja disekitarmu\n");
        }
    }
    else if (IsKataSama(processedInput, removeCustInput))
    { //COMMAND debug: remove
        Object *ClosestTable = Closest_Table(player, (player.currentMap));
        RemoveCustomerFromTable(ClosestTable);
    }
    else if (IsKataSama(processedInput, teleportDapurInput))
    {
        player.currentMap = &Kitchen;
        Move_Player(player.currentMap, &player, player.pos);
    }
    else if (IsKataSama(processedInput, teleportMap1Input))
    {
        player.currentMap = &Map1;
        Move_Player(player.currentMap, &player, player.pos);
    }
    else if (IsKataSama(processedInput, takeInput))
    {
        Object *Closest_Stove = Closest_Object(player, player.currentMap, STOVE);
        if (Closest_Stove != NULL)
        {
            printw("Kamu mengambil ItemID %d dari kompor!\n", ItemID(ArrayOfItem[(*Closest_Stove).data.stove.itemID]));
            Push_Stack(&player.hand, ArrayOfItem[(*Closest_Stove).data.stove.itemID]);
        }
        else
        {
            printw("Tidak ada kompor di sekitar player\n");
        }
    }
    else if (IsKataSama(processedInput, recipeInput))
    {
        BinTree P;
        FILE *fp;
        fp = fopen(NamaFile3, "r");
        if (fp == NULL)
            printw("File tidak terdeteksi\n");
        P = BuildBalanceTree(23, fp);
        printw("Berikut adalah resep makanan di game ini!\n\n");
        PrintTree(P, 3);
        printw("\n");
    }
}

void MainScreen()
{
    printw("Main Screen\n");
    char rawInput[10] = "";
    while (gameState == MAIN_MENU)
    {
        Create_New_Player(&player);
        printw("Welcome to Dapur Sadikin!\n");
        printw("What is your name?\n");
        printw("Name : ");
        scanf("%s", &rawInput);
        Set_Player_Name(&player, rawInput, 10);
        printw("Selamat datang, ");
        printKata(player.name);
        printw(".\n");
        gameState = IN_GAME;
    }
}

void MainGame()
{
    printw("Main Game\n");
    //PrintAllMemory(Map1);

    char rawInput[10] = "";

    CreateEmpty_Queue(&CustomerQueue, 5);

    while (gameState == IN_GAME)
    {
        /*
        printw("Map 1\n");
        Print_Room(Map1);
        printw("Map 2\n");
        Print_Room(Map2);
        printw("Map 3\n");
        Print_Room(Map3);
        printw("Dapur\n");
        Print_Kitchen(Kitchen);
        */
        printw("Input : ");
        scanf("%s", &rawInput);
        InputProcessor(rawInput, 10);
        Print_Room(*(player.currentMap));
        if (Life(player) <= 0)
        {
            printw("Dikarenakan banyak pelanggan yang tidak puas, akhirnya terjadi demo, dan restoranmu disegel oleh negara.\n");
            printw("GAME OVER!\n");
            gameState = CREDITS;
        }
    }
    DeAlokasi_Queue(&CustomerQueue);
    Dealokasi_All_Meja();
}