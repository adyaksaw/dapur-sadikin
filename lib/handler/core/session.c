#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "session.h"

WINDOW *m_pWin, *g_win;

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

int m_nXCoord = 0,
    m_nYCoord = 0,
    m_nWidth = 100,
    m_nHeight = 28,
    m_nPageSize = 20,
    m_nTopLine = 5,
    m_nScrWidth,
    m_nScrHeight,
    m_cTitleColor = (int)(COLOR_YELLOW),
    m_cCurrColor = (int)(COLOR_YELLOW),
    m_cStatusColor = (int)(COLOR_YELLOW),
    m_cCurrX = 0;
    m_cCurrY = 0;

char m_strTitle[20],
    m_strHeaders[100],
    m_strStatus[20];

void print_line_break()
{
    const char breakline[] = "*******";
    int n = 2;

    curs_set(0); // hide the cursor

    move(0.9 * m_nScrHeight, (m_nScrWidth - strlen(breakline) * n - 3) / 2);

    printw("***");
    refresh();

    while (n--)
    {
        //sleep(1);
        printw("%s", breakline);
        refresh();
    }

    //sleep(1);
    curs_set(1); 
}

void SaveToFile(char *FileName)
{
    int i;

    FILE *save;
    Stack handtemp;
    save = fopen(FileName, "w");
    //Player Info
    printKataToFile(Name(player), save);
    fprintf(save, "\n");
    //fprintf(save,"%s\n",Name(player).TabKata);
    fprintf(save, "%f %f %d\n", Absis(player.pos), Ordinat(player.pos), player.currentRoom);
    fprintf(save, "%ld\n", Money(player));
    fprintf(save, "%d\n", Life(player));
    fprintf(save, "%d\n", GameTime);
    Save_Stack(&Hand(player), save);
    fprintf(save, "ES 0\n");
    Save_Stack(&Food(player), save);
    fprintf(save, "ES 0\n");

    //Customer Queue
    Save_Queue(CustomerQueue, save);
    fprintf(save, "0 0 0 0 0\n"); //0 Adalah "tanda" yang menandakan Berakhirnya Pembacaan Queue

    //Table
    for (i = 1; i <= 12; i++)
    {
        Object M = *ArrayOfMeja[i];
        if (!IsOccupied(M))
        {
            fprintf(save, "%d %d\n", TableNumber(M), IsOccupied(M));
        }
        else
        {
            fprintf(save, "%d %d %d %d %d %d %d\n", TableNumber(M), IsOccupied(M), Amount(CustomerAt(M)), OrdersAt(M), Patience(CustomerAt(M)), Priority(CustomerAt(M)), Status(CustomerAt(M)));
        }
    }
    fprintf(save, "EQ\n");
    // printf("Save Sukses\n");
    fclose(save);
}

void LoadFromFile(char *FileName)
{
    int i;

    FILE *load;
    Stack handtemp;
    if (isPointValid(player.pos) && ElmtMx(*(player.currentMap), (int)Absis(player.pos), (int)Ordinat(player.pos)).tag == PLAYER_POS)
    {
        //printf("1\n");
        SetTag_Matrix(player.currentMap, (int)Absis((player).pos), (int)Ordinat((player).pos), EMPTY);
    }
    load = fopen(FileName, "r");
    //Player Info
    char raw_input[10] = "";
    fscanf(load, "%s", raw_input);
    isiKata(&Name(player), raw_input, 9);
    fscanf(load, "%f %f %d", &Absis(player.pos), &Ordinat(player.pos), &player.currentRoom);
    if (player.currentRoom == 1)
    {
        player.currentMap = &Map1;
    }
    else if (player.currentRoom == 2)
    {
        player.currentMap = &Map2;
    }
    else if (player.currentRoom == 3)
    {
        player.currentMap = &Map3;
    }
    else
    {
        player.currentMap = &Kitchen;
    }
    SetTag_Matrix(player.currentMap, (int)Absis((player).pos), (int)Ordinat((player).pos), PLAYER_POS);
    fscanf(load, "%ld", &Money(player));
    fscanf(load, "%d", &Life(player));
    fscanf(load, "%d", &GameTime);
    Input_Stack(&Hand(player), load);
    Input_Stack(&Food(player), load);
    //Customer Queue
    Load_Queue(&CustomerQueue, load);
    //printf("End Pembacaan Q\n");
    //Pembacaan berhenti saat pembacaan menemukan 0 sebagai nilai Amount,
    //Amount pastilah [1..4]

    //Table
    for (i = 1; i <= 12; i++)
    {
        //printf("Mantap");
        int NomerMeja;
        //TableNumber(*ArrayOfMeja[i])
        fscanf(load, "%d %d", &NomerMeja, &IsOccupied(*ArrayOfMeja[i]));
        //printf("%d Mantap\n", NomerMeja);
        //printf("%d", IsOccupied(*ArrayOfMeja[i]));
        if (IsOccupied(*ArrayOfMeja[i]) == 1)
        {
            Customer *customer = malloc(sizeof(Customer));
            fscanf(load, "%d %d %d %d %d", &Amount(*customer), &FoodOrderID(*customer), &Patience(*customer), &Priority(*customer), &Status(*customer));

            TableNum(*customer) = TableNumber(*ArrayOfMeja[i]);
            printCustomer(*customer);

            (*ArrayOfMeja[i]).data.table.customer_here = customer;
            (*ArrayOfMeja[i]).data.table.isOccupied = true;
            //printf("BINGITS\n");
        }
    }
    //printf("Load Sukses\n");
    fclose(load);
}
void PrintAllOrder()
{
    for (int i = 1; i <= 12; i++)
    {
        if (IsOccupied(*(ArrayOfMeja[i])))
        {
            printf("Meja No.%d memesan OrderID %d.\n", i, OrdersAt(*(ArrayOfMeja[i])));
        }
        else
        {
            printf("Meja No.%d kosong.\n", i);
        }
    }
}

void PrintTableStatus(Object Meja)
{
    printf("Nomor Meja: %d\n", TableNumber(Meja));
    printf("IsOccupied: %d\n", IsOccupied(Meja));
    if (IsOccupied(Meja))
    {
        printf("Patience: %d\n", Patience(CustomerAt(Meja)));
        printf("Jumlah orang: %d\n", Amount(CustomerAt(Meja)));
        printCustomer(CustomerAt(Meja));
    }
}

void PrintAllMemory(Matrix *M)
{
    for (int i = 1; i <= 8; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            printf("ALAMAT MEMORY M KE %d-%d adalah %p.\n", i, j, &((*M).Mem[i][j]));
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

void Initialize_Session()
{
    CreateBigMap(&Map1, &Map2, &Map3, &Kitchen, &BIG_MAP);
    int i;
    srand(time(NULL));
    Create_New_Player(&player);
    LoadMap(&Map1, &Map2, &Map3, &Kitchen);

    FILE *fp;
    fp = fopen(NamaFile3, "r");
    if (fp == NULL)
        printf("File tidak terdeteksi\n");
    resep = BuildBalanceTree(23, fp);

    // for (i = 1; i <= 23; i++)
    // {
    //     ArrayOfItem[i] = SearchItemTree(resep, i);
    //     printf("Nama item ke %d: ", i);
    //     printKata((ArrayOfItem[i].name));
    //     printf(" %d\n", ItemID(ArrayOfItem[i]));
    // }

    GameTime = 0;
    //printf("Init\n");
    //PrintAllMemory(&Map1);
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
    float customerAppearChance = 100 * (1 - sqrt(1.0 / GameTime));
    if (!IsFull_Queue(CustomerQueue) && (rand() % 100) + 1 <= customerAppearChance)
    {
        Customer *newCustomer;
        newCustomer = GenerateCustomer();

        printf("New Customer\n");
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
                    printf("Terlalu lama menunggu, ada pelanggan di antrian yang bosan dan memilih makan di geprek.\n");
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
                    printf("Terlalu lama menunggu, ada pelanggan di antrian yang bosan dan memilih makan di geprek.\n");
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
                printf("Terlalu lama menunggu, pelanggan di meja %d bosan dan memilih makan di geprek.\n", i);
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

    Kata saveInput;
    isiKata(&saveInput, "save", 4);

    Kata loadInput;
    isiKata(&loadInput, "load", 4);

    if (IsKataSama(processedInput, quitInput))
    { //COMMAND quit
        erase();
        refresh();

        gameState = CREDITS;
        Credits();
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
        PrintData_Stack(player.hand, 1);
    }
    else if (IsKataSama(processedInput, buangTanganInput))
    { //COMMAND CH
        CreateEmpty_Stack(&(player.hand));
    }
    else if (IsKataSama(processedInput, nampanInput))
    { //COMMAND tray
        PrintData_Stack(player.food, 0);
    }
    else if (IsKataSama(processedInput, buangNampanInput))
    { //COMMAND CH
        CreateEmpty_Stack(&(player.food));
    }
    else if (IsKataSama(processedInput, putInput))
    { //COMMAND CH
        Object *Closest_Tray = Closest_Object(player, player.currentMap, TRAY);
        if (Closest_Tray != NULL)
        {
            Masak(&player, resep);
        }
        else
        {
            printf("Tidak ada nampan disekitarmu!\n");
        }
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
                    printf("Pesanan di meja nomor %d adalah FoodID %d, yaitu ", TableNumber(*ClosestTable), OrdersAt(*ClosestTable));
                    printKata(ArrayOfItem[OrdersAt(*ClosestTable)].name);
                    printf(".\n");
                }
                else
                {
                    printf("Customer pada meja %d telah memesan FoodID %d, yaitu ", TableNumber(*ClosestTable), OrdersAt(*ClosestTable));
                    printKata(ArrayOfItem[OrdersAt(*ClosestTable)].name);
                }
            }
            else
            {
                printf("Meja nomor %d kosong.\n", TableNumber(*ClosestTable));
            }
        }
        else
        {
            printf("Tidak ada meja kosong disekitarmu!\n");
        }
    }
    else if (IsKataSama(processedInput, placeInput))
    { //COMMAND place
        Object *ClosestTable = Closest_Empty_Table(player, (player.currentMap));
        if (ClosestTable != NULL)
        {
            printf("Meja dengan nomor %d kosong.\n", (*ClosestTable).data.table.num);
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
                        printf("Tidak ada customer yang valid untuk meja ini\n");
                    }
                }
                if (IsOccupied(*ClosestTable))
                {
                    printf("Sekarang meja nomor %d sudah diduduki.\n", TableNumber(*ClosestTable));
                }
            }
            else
            {
                printf("Antrian kosong.\n");
            }
        }
        else
        {
            printf("Tidak ada meja kosong disekitarmu!\n");
        }
    }
    else if (IsKataSama(processedInput, helpInput))
    { //COMMAND help
        mvwprintw(m_pWin, 5, 23, "Ketik help untuk melihat daftar command.\n");
        mvwprintw(m_pWin, 6, 23, "Ketik GU untuk memindahkan player ke atas.\n");
        mvwprintw(m_pWin, 7, 23, "Ketik GD untuk memindahkan player ke bawah.\n");
        mvwprintw(m_pWin, 8, 23, "Ketik GL untuk memindahkan player ke kiri.\n");
        mvwprintw(m_pWin, 9, 23, "Ketik GR untuk memindahkan player ke kanan.\n");
        mvwprintw(m_pWin, 10, 23, "Ketik allOrder untuk melihat order setiap meja.\n");
        mvwprintw(m_pWin, 11, 23, "Ketik queue untuk melihat antrian saat ini.\n");
        mvwprintw(m_pWin, 12, 23, "Ketik status untuk melihat status pemain.\n");
        mvwprintw(m_pWin, 13, 23, "Ketik place untuk menaruh customer di meja.\n");
        mvwprintw(m_pWin, 14, 23, "Ketik give untuk menyajikan makanan dari tray.\n");
        mvwprintw(m_pWin, 15, 23, "Ketik take untuk mengambil bahan dari kompor.\n");
        mvwprintw(m_pWin, 16, 23, "Ketik recipe untuk melihat resep yang ada.\n");
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
                    Money(player) += FoodPrice * (1 + (Patience(*Cust) + Priority(*Cust) + Amount(*Cust)) / FoodPriceModifier);
                    printf("Pelanggan tersebut puas dengan makanannya!\n");
                    printf("Kamu mendapatkan %d\n", FoodPrice * (1 + (Patience(*Cust) + Priority(*Cust) + Amount(*Cust)) / FoodPriceModifier));
                    RemoveCustomerFromTable(ClosestTable);
                }
                else if (IsEmpty_Stack(player.food))
                {
                    printf("Nampan kosong\n");
                }
                else
                {
                    printf("Makanan di nampan paling atas tidak sesuai dengan keinginan customer ini\n");
                }
            }
            else
            {
                printf("Tidak ada customer di meja tersebut\n");
            }
        }
        else
        {
            printf("Tidak ada meja disekitarmu\n");
        }
    }
    else if (IsKataSama(processedInput, removeCustInput))
    { //COMMAND debug: remove
        Object *ClosestTable = Closest_Table(player, (player.currentMap));
        RemoveCustomerFromTable(ClosestTable);
    }
    else if (IsKataSama(processedInput, takeInput))
    { // COMMAND take
        Object *Closest_Stove = Closest_Object(player, player.currentMap, STOVE);
        if (Closest_Stove != NULL)
        {

            printf("Kamu mengambil ItemID %d dari kompor, yaitu: ", (*Closest_Stove).data.stove.itemID);
            printKata((ArrayOfItem[(*Closest_Stove).data.stove.itemID].name));
            Push_Stack(&player.hand, ArrayOfItem[(*Closest_Stove).data.stove.itemID]);
        }
        else
        {
            printf("Tidak ada kompor di sekitar player\n");
        }
    }
    else if (IsKataSama(processedInput, recipeInput))
    { // COMMAND recipe
        printf("Berikut adalah resep makanan di game ini!\n\n");
        PrintTree(resep, 3);
        printf("\n");
    }
    else if (IsKataSama(processedInput, loadInput))
    {
        LoadFromFile("save.txt");
    }
    else if (IsKataSama(processedInput, saveInput))
    {
        SaveToFile("Save.txt");
    }
}

void Print_Screen()
{
    printf("\n|-----------------------------------------------------------------------------------------------|\n");
    printf("| Welcome, ");
    printKata(player.name);
    printf("!\t   |");
    printf("\tMoney:\t\t%d\t\t|", Money(player));
    printf("   Life:\t%d   |", Life(player));
    printf("\tTime:\t%d\t|", GameTime);
    printf("\n");
    printf("|-----------------------------------------------------------------------------------------------|\n");
    printf("  Waiting cust: %d\n\n", NBElmt_Queue(CustomerQueue));
    Print_Room(*(player.currentMap));
    printf("|-----------------------------------------------------------------------------------------------|\n");
    printf("Food stack: \n");
    PrintData_Stack(Food(player), true);
    printf("|-----------------------------------------------------------------------------------------------|\n");
    printf("Hand: \n");
    PrintData_Stack(Hand(player), true);
}

void EnableRawInput()
{
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

void DisableRawInput()
{
    noraw();
    echo();
    keypad(stdscr, FALSE);
}

void Menu(int height, int width, int offX, int offY, char *choices[], char *choices2[], char *ret)
{
    WINDOW *my_menu_win;
    ITEM **my_items;
    int c;
    MENU *my_menu;
    int n_choices, i, con = 1;
    ITEM *cur_item;

    EnableRawInput();

    n_choices = ARRAY_SIZE(choices) + 1;
    my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

    /* Create items */
    for (i = 0; i < n_choices; ++i)
        my_items[i] = new_item(choices[i], choices2[0]);
    my_items[n_choices] = (ITEM *)NULL;

    /* Crate menu */
    my_menu = new_menu((ITEM **)my_items);

    /* Create the window to be associated with the menu */
    my_menu_win = newwin(height, width, m_nScrHeight / 2 - height/2 + offY, m_nScrWidth / 2 - width/2 + offX);
    keypad(my_menu_win, TRUE);

    /* Set main window and sub window */
    set_menu_win(my_menu, my_menu_win);
    set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));

    /* Set menu mark to the string " * " */
    set_menu_mark(my_menu, " * ");

    //box(my_menu_win, 0, 0);
    refresh();

    /* Post the menu */
    post_menu(my_menu);
    wrefresh(my_menu_win);

    do
    {
        c = wgetch(my_menu_win);

        switch (c)
        {
        case KEY_DOWN:
            menu_driver(my_menu, REQ_DOWN_ITEM);
            break;
        case KEY_UP:
            menu_driver(my_menu, REQ_UP_ITEM);
            break;
        case 10:
            {
                *ret = item_name(current_item(my_menu))[1];
                con = 0;
                break;
            }
        }
    }
    while (con);

    unpost_menu(my_menu);
    free_menu(my_menu);
    for (i = 0; i < n_choices; ++i)
        free_item(my_items[i]);
    DisableRawInput();
    endwin();
}

void MainScreen()
{
    //printf("Main Screen\n");
    const char mesg1[] = "Welcome to Dapur Sadikin!";
    const char mesg2[] = "Name: ";
    const char mesg3[] = "Good to see you again.";
    char rawInput[100] = "";
    int width = 80, height = 20;
    char *choices[] = {
        " LOAD SAVED",
        " NEW GAME",
        };
    char *empty[] = {""};
    char ret;

    WINDOW *new_win;

    refresh();
    new_win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
    box(new_win, 0, 0);
    wrefresh(new_win);

    attron(A_BOLD);
    mvprintw(m_nScrHeight / 2 - 2, (m_nScrWidth - strlen(mesg1)) / 2, "%s", mesg1);
    attroff(A_BOLD);

    Menu(9, 40, 10, 3,choices, empty, &ret);

    refresh();
    new_win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
    box(new_win, 0, 0);
    wrefresh(new_win);

    attron(A_BOLD);
    mvprintw(m_nScrHeight / 2 - 2, (m_nScrWidth - strlen(mesg1)) / 2, "%s", mesg1);
    attroff(A_BOLD);

    if(ret == 'N')
    {
        Create_New_Player(&player);

        mvprintw(m_nScrHeight / 2 + 1, (m_nScrWidth - strlen(mesg2)) / 2 - 5, "%s", mesg2);

        getstr(rawInput);
        //scanf("%s", &rawInput);

        Set_Player_Name(&player, rawInput, strlen(rawInput) + 1);
    }
    else
    {
        LoadFromFile("save.txt");
        mvprintw(m_nScrHeight / 2 + 1, (m_nScrWidth - strlen(mesg3)) / 2, "%s", mesg3);
    }

    LINE_BREAK;
    gameState = IN_GAME;

}

void MainGame()
{
    char rawInput[10] = "", c;
    int height = 20;
    int width = 50;

    Draw_Dynamic_Items(m_pWin);
    CreateEmpty_Queue(&CustomerQueue, 5);

    g_win = newwin(height, width, (LINES - height) / 2 + 1, (COLS - width) / 2 - 2);
    box(g_win, 0 ,0);
    wprintw(g_win, "gdfasfsd");

    while (gameState == IN_GAME)
    {
        Draw_Dynamic_Items(m_pWin);
        refresh();
        wrefresh(m_pWin);
        wrefresh(g_win);
        wmove(m_pWin, m_cCurrY, m_cCurrX);
        wclrtoeol(m_pWin);
        wgetstr(m_pWin, rawInput);
        // Print_Screen();
        // printf("|-----------------------------------------------------------------------------------------------|\n");
        // printf("\nInput : ");
        // scanf("%s", &rawInput);
        wmove(m_pWin, 5, 23);
        InputProcessor(rawInput, 10);

        // if (Life(player) <= 0)
        // {
        //     printf("Dikarenakan banyak pelanggan yang tidak puas, akhirnya terjadi demo, dan restoranmu disegel oleh negara.\n");
        //     printf("GAME OVER!\n");
        //     gameState = CREDITS;
        // }
        Draw_Dynamic_Items(m_pWin);
    }
    DeAlokasi_Queue(&CustomerQueue);
    Dealokasi_All_Meja();
}

void Credits()
{
    const char mesg[] = "Save game?";
    const char mesgg[] = "Game saved.";
    char *choices[] = {
        " YES",
        " NO",
    };
    char *empty[] = {""};
    char ret;

    attron(A_BOLD);
    mvprintw(m_nScrHeight / 2 - 3, (m_nScrWidth - strlen(mesg)) / 2 , "%s", mesg);
    attroff(A_BOLD);

    Menu(9, 40, 14, 2, choices, empty, &ret);

    clear();
    refresh();

    if(ret == 'Y'){
        SaveToFile("save.txt");
        mvprintw(m_nScrHeight / 2 + 8, (m_nScrWidth - strlen(mesgg)) / 2, "%s", mesgg);
    }

    const char mesg1[] = "Thank you for playing!";
    const char mesg2[] = "Courtesy of DAPUR SADIKIN @2018";

    attron(A_BOLD);
    mvprintw(m_nScrHeight / 2 - 1, (m_nScrWidth - strlen(mesg1)) / 2, "%s", mesg1);
    attroff(A_BOLD);

    mvprintw(m_nScrHeight / 2 + 1, (m_nScrWidth - strlen(mesg2)) / 2, "%s", mesg2);

    refresh();

    LINE_BREAK;
}

/*
    notif line (below table)

    inside panel:
    map (layer printmap, retrieve from getmap. layer input, pass to input processor)
    recipe (multilevel list ?)
    status
    help
    allorder
    - BACK BUTTON

    side panel :
    queue  (limit display)
    order
    tray
    hand
*/

void Draw_Window()
{
    // update the screen width/height variables and make sure that the window will
    // still fit in case the user happens to resize their terminal (e.g., xterm);
    // throws an exception if screen too small in either direction
    checkScreenSize();

    m_pWin = newwin(m_nHeight, m_nWidth, m_nYCoord, m_nXCoord);
    box(m_pWin, 0, 0);

    Draw_Static_Items();
    //Draw_Dynamic_Items();

    refresh();
    wrefresh(m_pWin);
}

void Draw_Static_Items()
{
    strcpy(m_strTitle, "DAPUR SADIKIN");
    strcpy(m_strHeaders, " Name:             |   Money:                    |  Life:                 |  Time:     ");
    strcpy(m_strStatus, "Command: ");

    // title, centered
    wattron(m_pWin, A_BOLD);
    mvwprintw(m_pWin, 1, (m_nWidth / 2) - strlen(m_strTitle) / 2, "%s", m_strTitle);
    wattroff(m_pWin, A_BOLD);

    // line underneath the title
    mvwhline(m_pWin, 2, 1, 0, m_nWidth - 2);
    mvwhline(m_pWin, 14, 1, 0, 20);
    mvwhline(m_pWin, 14, 76, 0, 23);
    mvwaddch(m_pWin, 2, 0, ACS_LTEE);
    mvwaddch(m_pWin, 2, 20, ACS_TTEE);
    mvwaddch(m_pWin, 2, 50, ACS_TTEE);
    mvwaddch(m_pWin, 2, 75, ACS_TTEE);

    // headers
    mvwprintw(m_pWin, 3, 1, "%s", m_strHeaders);
    mvwprintw(m_pWin, 5, 2, "Waiting customer:");
    mvwprintw(m_pWin, 5, 77, "Tray:");
    mvwprintw(m_pWin, 15, 2, "Orders:");
    mvwprintw(m_pWin, 15, 77, "Hand:");

    // separators between the headers
    mvwaddch(m_pWin, 3, 20, ACS_VLINE);
    mvwaddch(m_pWin, 3, 50, ACS_VLINE);
    mvwaddch(m_pWin, 3, 75, ACS_VLINE);

    // line underneath the headers
    mvwhline(m_pWin, 4, 1, 0, m_nWidth - 2);
    mvwhline(m_pWin, 4, 1, 0, m_nWidth - 2);
    mvwaddch(m_pWin, 4, 0, ACS_LTEE);
    mvwaddch(m_pWin, 4, 20, ACS_PLUS);
    mvwaddch(m_pWin, 4, 50, ACS_BTEE);
    mvwaddch(m_pWin, 4, 75, ACS_PLUS);

    // column separators in the ASCII list view
    for (int iii = 0; iii < m_nPageSize; iii++)
    {
        mvwaddch(m_pWin, m_nTopLine + iii, 20, ACS_VLINE);
        mvwaddch(m_pWin, m_nTopLine + iii, 75, ACS_VLINE);
    }

    // line above the status text
    mvwhline(m_pWin, 25, 1, 0, m_nWidth - 2);
    mvwhline(m_pWin, 25, 1, 0, m_nWidth - 2);
    mvwaddch(m_pWin, 25, 0, ACS_LTEE);
    mvwaddch(m_pWin, 25, 20, ACS_BTEE);
    mvwaddch(m_pWin, 25, 75, ACS_BTEE);

    // status text
    wattron(m_pWin, A_BOLD);
    mvwprintw(m_pWin, 26, 3, "%s", m_strStatus);
    getyx(m_pWin, m_cCurrY, m_cCurrX);
    
    wattroff(m_pWin, A_BOLD);
}

void Draw_Dynamic_Items()
{
    // headers
    int i = 1;
    while (i < Name(player).Length && Name(player).TabKata[i] != '\0')
    {
        mvwprintw(m_pWin, 3, 7 + i, "%c", Name(player).TabKata[i]);
        i++;
    }
    mvwprintw(m_pWin, 3, 45, "%d", Money(player));
    mvwprintw(m_pWin, 3, 70, "%d", Life(player));
    mvwprintw(m_pWin, 3, 95, "%d", GameTime);

    mvwprintw(m_pWin, 6, 2, "%d", NBElmt_Queue(CustomerQueue));
    mvwprintw(m_pWin, 6, 2, "%d", NBElmt_Queue(CustomerQueue));

    //drawPanel();
}
