#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "session.h"

int m_nXCoord = 0,
    m_nYCoord = 0,
    m_nWidth = 100,
    m_nHeight = 35,
    m_nPageSize = 27,
    m_nTopLine = 5,
    m_nScrWidth,
    m_nScrHeight,
    m_cTitleColor = (int)(COLOR_YELLOW),
    m_cCurrColor = (int)(COLOR_YELLOW),
    m_cStatusColor = (int)(COLOR_YELLOW),
    m_cCurrX = 0,
    m_cCurrY = 0,
    m_gOver = 0;

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
        sleep(1);
        printw("%s", breakline);
        refresh();
    }

    sleep(1);
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
    //fprintf(save,"%s\n",Name(wprintw(g_win, player).TabKata);
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
    //printf("Save Sukses\n");
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

void PrintOrder()
{
    int n = 1;
    for (int i = 1; i <= 12; i++)
    {
        if (IsOccupied(*(ArrayOfMeja[i])))
        {
            mvwprintw(m_pWin, 16, 2 + n, "ID %d, %d", OrdersAt(*(ArrayOfMeja[i])), i);
            n++;
        }
    }
}

void PrintAllOrder()
{
    for (int i = 1; i <= 12; i++)
    {
        if (IsOccupied(*(ArrayOfMeja[i])))
        {
            wprintw(g_win, "Meja No.%d memesan OrderID %d.\n", i, OrdersAt(*(ArrayOfMeja[i])));
        }
        else
        {
            wprintw(g_win, "Meja No.%d kosong.\n", i);
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

    for (i = 1; i <= 23; i++)
    {
        ArrayOfItem[i] = SearchItemTree(resep, i);
        //printf("Nama item ke %d: ", i);
        //printKata((ArrayOfItem[i].name));
        //printf(" %d\n", ItemID(ArrayOfItem[i]));
    }
    // PrintTree(resep, 2);

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
                    mvwprintw(g_win, 11, 0, "Terlalu lama menunggu, ada pelanggan di antrian yang bosan dan memilih makan di geprek.\n");
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
                    mvwprintw(g_win, 11, 0, "Terlalu lama menunggu, ada pelanggan di antrian yang bosan dan memilih makan di geprek.\n");
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
                mvwprintw(g_win, 11, 0, "Terlalu lama menunggu, pelanggan di meja %d bosan dan memilih makan di geprek.\n", i);
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

void printCustomerW(Customer customer)
{
    wprintw(g_win, "%d orang. Meja %d. Kesabaran %d. Prioritas %d. Status %d", Amount(customer), TableNum(customer), Patience(customer), Priority(customer), Status(customer));
}

void InputProcessor(char input[], int input_length)
{
    int height = 27;
    int width = 52;

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
        //Print_Player(player);
        wprintw(g_win, "Nama : ");
        // int i = 1;
        // while (i <= Name(player).Length && Name(player).TabKata[i] != '\0')
        // {
        //     wprintw(g_win, "%c", Name(player).TabKata[i]);
        //     i++;
        // }
        printKataWaja(player.name, g_win);
        wprintw(g_win, "\n");
        wprintw(g_win, "Uang : %d\n", player.money);
        wprintw(g_win, "Nyawa : %d\n", player.life);
        wprintw(g_win, "Posisi Baris %.1f Kolom %.1f.\n", Absis(player.pos), Ordinat(player.pos));
        return;
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
        //Print_Queue(CustomerQueue);
        wprintw(g_win, "Customer di Queue:\n");
        int HeadID = Head(CustomerQueue);
        if (HeadID < Tail(CustomerQueue))
        {
            while (HeadID <= Tail(CustomerQueue))
            {
                printCustomerW(*(CustomerQueue.T[HeadID]));
                HeadID++;
            }
        }
        else if (HeadID > Tail(CustomerQueue))
        {
            while (HeadID != Tail(CustomerQueue))
            {
                printCustomerW(*(CustomerQueue.T[HeadID]));
                HeadID++;
                if (HeadID > MaxEl(CustomerQueue))
                {
                    HeadID -= MaxEl(CustomerQueue);
                }
            }
            if (HeadID == Tail(CustomerQueue))
            {
                printCustomerW(*(CustomerQueue.T[HeadID]));
            }
        }
        else
        {
            if (HeadID != Nil_Queue && HeadID == Tail(CustomerQueue))
            {
                printCustomerW(*(CustomerQueue.T[HeadID]));
            }
            else
            {
                wprintw(g_win, "Queue kosong.\n");
            }
        }
        return;
    }
    else if (IsKataSama(processedInput, allOrderInput))
    { //COMMAND allOrder
        PrintAllOrder();
        return;
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
    {                                    //COMMAND hand
        PrintData_Stack(player.hand, 1); //DISKIP
    }
    else if (IsKataSama(processedInput, buangTanganInput))
    { //COMMAND CH
        CreateEmpty_Stack(&(player.hand));
    }
    else if (IsKataSama(processedInput, nampanInput))
    {                                    //COMMAND tray
        PrintData_Stack(player.food, 0); //DISKIP
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
            PrintNotif("Tidak ada nampan disekitarmu!");
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

                    mvwprintw(g_win, 11, 2, "Pesanan di meja nomor %d adalah FoodID %d, yaitu:", TableNumber(*ClosestTable), OrdersAt(*ClosestTable));
                }
                else
                {
                    mvwprintw(g_win, 11, 1, "Customer pada meja %d telah memesan FoodID %d, yaitu ", TableNumber(*ClosestTable), OrdersAt(*ClosestTable));
                    //printf("Customer pada meja %d telah memesan FoodID %d, yaitu ", TableNumber(*ClosestTable), OrdersAt(*ClosestTable));
                    printKataW(ArrayOfItem[OrdersAt(*ClosestTable)].name, g_win, 13, 7);
                }
                // int j = 1;
                // while (j < ArrayOfItem[OrdersAt(*ClosestTable)].name.Length && ArrayOfItem[OrdersAt(*ClosestTable)].name.TabKata[j] != '\0')
                // {
                //     mvwprintw(g_win, 13, j + 6, "%c", ArrayOfItem[OrdersAt(*ClosestTable)].name.TabKata[j]);
                //     j++;
                // }
                return;
            }
            else
            {
                //printf("Meja nomor %d kosong.\n", TableNumber(*ClosestTable));
                PrintNotif("Meja kosong.");
            }
        }
        else
        {
            PrintNotif("Tidak ada meja kosong di sekitarmu!");
        }
    }
    else if (IsKataSama(processedInput, placeInput))
    { //COMMAND place
        Object *ClosestTable = Closest_Empty_Table(player, (player.currentMap));
        if (ClosestTable != NULL)
        {
            //printf("Meja dengan nomor %d kosong.\n", (*ClosestTable).data.table.num);
            PrintNotif("Meja ini kosong.");
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
                        PrintNotif("Tidak ada customer yang valid untuk meja ini.");
                    }
                }
                if (IsOccupied(*ClosestTable))
                {
                    //printf("Sekarang meja nomor %d sudah diduduki.", TableNumber(*ClosestTable));
                    PrintNotif("Meja sekarang sudah diduduki.");
                }
            }
            else
            {
                PrintNotif("Antrian kosong.");
            }
        }
        else
        {
            PrintNotif("Tidak ada meja kosong di sekitarmu!");
        }
    }

    else if (IsKataSama(processedInput, helpInput))
    { //COMMAND help
        wprintw(g_win, "Ketik help untuk melihat daftar command.\n");
        wprintw(g_win, "Ketik GU untuk memindahkan player ke atas.\n");
        wprintw(g_win, "Ketik GD untuk memindahkan player ke bawah.\n");
        wprintw(g_win, "Ketik GL untuk memindahkan player ke kiri.\n");
        wprintw(g_win, "Ketik GR untuk memindahkan player ke kanan.\n");
        wprintw(g_win, "Ketik allOrder untuk melihat order setiap meja.\n");
        wprintw(g_win, "Ketik queue untuk melihat antrian saat ini.\n");
        wprintw(g_win, "Ketik status untuk melihat status pemain.\n");
        wprintw(g_win, "Ketik place untuk menaruh customer di meja.\n");
        wprintw(g_win, "Ketik give untuk menyajikan makanan dari tray.\n");
        wprintw(g_win, "Ketik take untuk mengambil bahan dari kompor.\n");
        wprintw(g_win, "Ketik recipe untuk melihat resep yang ada.\n");
        return;
    }
    else if (IsKataSama(processedInput, giveInput))
    { //COMMAND give
        Object *ClosestTable = Closest_Table(player, (player.currentMap));
        if (ClosestTable != NULL)
        {
            if ((*ClosestTable).data.table.isOccupied)
            {
                Customer *Cust = (*ClosestTable).data.table.customer_here;
                if (FoodOrderID(*Cust) == ItemID(InfoTop(player.food)) && !IsEmpty_Stack(Food(player)))
                {
                    Money(player) += FoodPrice * (1 + (Patience(*Cust) + Priority(*Cust) + Amount(*Cust)) / FoodPriceModifier);
                    mvwprintw(g_win, 11, 5, "Pelanggan tersebut puas dengan makanannya!");
                    mvwprintw(g_win, 13, 15, "Kamu mendapatkan %d\n", FoodPrice * (1 + (Patience(*Cust) + Priority(*Cust) + Amount(*Cust)) / FoodPriceModifier));
                    RemoveCustomerFromTable(ClosestTable);
                    return;
                }
                else if (IsEmpty_Stack(player.food))
                {
                    PrintNotif("Nampan kosong.");
                }
                else
                {
                    PrintNotif("Makanan di nampan paling atas tidak sesuai dengan keinginan customer ini.");
                }
            }
            else
            {
                PrintNotif("Tidak ada customer di meja tersebut.");
            }
        }
        else
        {
            PrintNotif("Tidak ada meja disekitarmu.");
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
            // PROBLEM here
            mvwprintw(g_win, 11, 4, "Kamu mengambil ItemID %d dari kompor, yaitu: ", ItemsIn(*Closest_Stove));
            printKataW((ArrayOfItem[(*Closest_Stove).data.stove.itemID].name), g_win, 13, 6);

            // int j = 1;
            // while (j < (ArrayOfItem[ItemsIn(*Closest_Stove)].name).Length && (ItemName(ArrayOfItem[ItemsIn(*Closest_Stove)])[j] != '\0'))
            // {
            //     mvwprintw(g_win, 12, j, "%c", (ItemName(ArrayOfItem[ItemsIn(*Closest_Stove)]))[j]);
            //     j++;
            // }
            Push_Stack(&player.hand, ArrayOfItem[(*Closest_Stove).data.stove.itemID]);
            return;
        }
        else
        {
            PrintNotif("Tidak ada kompor di sekitar player.");
        }
    }
    else if (IsKataSama(processedInput, recipeInput))
    { // COMMAND recipe
        wprintw(g_win, "Berikut adalah resep makanan di game ini!\n\n");
        PrintTreee(resep, 3);
        return;
    }
    else if (IsKataSama(processedInput, loadInput))
    {
        LoadFromFile("Save.txt");
    }
    else if (IsKataSama(processedInput, saveInput))
    {
        SaveToFile("Save.txt");
    }
    Print_RoomW(*(player.currentMap));
}

void PrintNotif(char *s)
{
    mvwprintw(g_win, 25, 26 - (strlen(s) + 4) / 2, "- %s -", s);
    wmove(g_win, 0, 0);
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
    my_menu_win = newwin(height, width, m_nScrHeight / 2 - height / 2 + offY, m_nScrWidth / 2 - width / 2 + offX);
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
    } while (con);

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

    Menu(9, 40, 10, 3, choices, empty, &ret);

    refresh();
    new_win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
    box(new_win, 0, 0);
    wrefresh(new_win);

    attron(A_BOLD);
    mvprintw(m_nScrHeight / 2 - 2, (m_nScrWidth - strlen(mesg1)) / 2, "%s", mesg1);
    attroff(A_BOLD);

    if (ret == 'N')
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
    const char mesg1[] = "Dikarenakan banyak pelanggan yang tidak puas,";
    const char mesg2[] = "terjadi demo, dan restoranmu disegel oleh negara.";
    const char mesg3[] = "GAME OVER!";
    char rawInput[10] = "";
    int height = 27;
    int width = 52;

    Draw_Dynamic_Items(m_pWin);
    CreateEmpty_Queue(&CustomerQueue, 5);

    g_win = newwin(height, width, (LINES - height) / 2 + 1, (COLS - width) / 2 - 2);
    //box(g_win, 0, 0);
    sleep(1);
    Print_RoomW(*(player.currentMap));

    while (gameState == IN_GAME)
    {
        wrefresh(g_win);

        wmove(m_pWin, m_cCurrY, m_cCurrX);
        wclrtoeol(m_pWin);

        wgetstr(m_pWin, rawInput);

        wclear(g_win);

        InputProcessor(rawInput, 10);

        if (Life(player) <= 0)
        {
            m_gOver = 1;
            wclear(g_win);
            mvwprintw(g_win, height / 2 - 3, width / 2 - strlen(mesg1) / 2, "%s", mesg1);
            mvwprintw(g_win, height / 2 - 2, width / 2 - strlen(mesg2) / 2, "%s", mesg2);

            wattron(g_win, A_BOLD);
            mvwprintw(g_win, height / 2 + 1, width / 2 - strlen(mesg3) / 2, "%s", mesg3);
            wattroff(g_win, A_BOLD);

            wrefresh(g_win);

            getch();
            gameState = CREDITS;
        }

        Draw_Dynamic_Items(m_pWin);
        wrefresh(m_pWin);
    }
    DeAlokasi_Queue(&CustomerQueue);
    Dealokasi_All_Meja();
}

void Credits()
{
    if (!m_gOver)
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
        mvprintw(m_nScrHeight / 2 - 3, (m_nScrWidth - strlen(mesg)) / 2, "%s", mesg);
        attroff(A_BOLD);

        Menu(9, 40, 14, 2, choices, empty, &ret);

        if (ret == 'Y')
        {
            SaveToFile("save.txt");
            mvprintw(m_nScrHeight / 2 + 8, (m_nScrWidth - strlen(mesgg)) / 2, "%s", mesgg);
        }
    }

    clear();
    refresh();

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
*/

void Draw_Window()
{
    // update the screen width/height variables and make sure that the window will
    // still fit in case the user happens to resize their terminal (e.g., xterm);
    // throws an exception if screen too small in either direction
    //checkScreenSize();

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
    mvwhline(m_pWin, 20, 76, 0, 23);
    mvwaddch(m_pWin, 2, 0, ACS_LTEE);
    mvwaddch(m_pWin, 2, 20, ACS_TTEE);
    mvwaddch(m_pWin, 2, 50, ACS_TTEE);
    mvwaddch(m_pWin, 2, 75, ACS_TTEE);

    // headers
    mvwprintw(m_pWin, 3, 1, "%s", m_strHeaders);
    mvwprintw(m_pWin, 5, 2, "Waiting customer:");
    mvwprintw(m_pWin, 5, 77, "Tray:");
    mvwprintw(m_pWin, 15, 2, "Orders:");
    mvwprintw(m_pWin, 21, 77, "Hand:");

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
    mvwhline(m_pWin, 32, 1, 0, m_nWidth - 2);
    mvwhline(m_pWin, 32, 1, 0, m_nWidth - 2);
    mvwaddch(m_pWin, 32, 0, ACS_LTEE);
    mvwaddch(m_pWin, 32, 20, ACS_BTEE);
    mvwaddch(m_pWin, 32, 75, ACS_BTEE);

    // status text
    wattron(m_pWin, A_BOLD);
    mvwprintw(m_pWin, 33, 3, "%s", m_strStatus);
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
    mvwprintw(m_pWin, 3, 40, "%d", Money(player));
    mvwprintw(m_pWin, 3, 70, "%d", Life(player));
    mvwprintw(m_pWin, 3, 95, "%d", GameTime);

    mvwprintw(m_pWin, 6, 2, "%d", NBElmt_Queue(CustomerQueue));
    //mvwprintw(m_pWin, 16, 2, "%d", NBElmt_Queue(CustomerQueue));
    PrintOrder();

    //mvwprintw(m_pWin, 6, 77, "Anda tidak memegang apapun");
    PrtStk(Food(player), 6, 77);
    PrtStk(Hand(player), 22, 77);

    //drawPanel();
}

void printKataW(Kata k, WINDOW *w, int row, int col)
{
    int i = 1;
    while (i <= k.Length && k.TabKata[i] != '\0')
    {
        mvwprintw(w, row, col - 1 + i, "%c", k.TabKata[i]);
        i++;
    }
}

void printKataWaja(Kata k, WINDOW *w)
{
    int i = 1;
    while (i <= k.Length && k.TabKata[i] != '\0')
    {
        wprintw(w, "%c", k.TabKata[i]);
        i++;
    }
}

void PrtStk(Stack S, int row, int col)
{
    if (IsEmpty_Stack(S))
    {
        mvwprintw(m_pWin, row, col, "<kosong>");
        for (int i = 1; i <= 6; i++)
            mvwprintw(m_pWin, row + i, col, "               ");
    }
    else
    {
        for (int i = 1; i <= Top(S); i++)
        {
            mvwprintw(m_pWin, row - 1 + i, col, "               ");
            mvwprintw(m_pWin, row - 1 + i, col, "[%d]", i);
            printKataW(S.T[i].name, m_pWin, 3, 7);
            // int j = 1;
            // while (j < S.T[i].name.Length && S.T[i].name.TabKata[j] != '\0')
            // {
            //     mvwprintw(m_pWin, 3, 7 + j, "%c", S.T[i].name.TabKata[j]);
            //     j++;
            // }
        }
    }
}

void PrintTreeWithIndentt(BinTree P, int h, int idt)
{
    int i;
    if (!IsTreeEmpty(P))
    {
        wprintw(g_win, "%d ", Akar(P).id);
        printKataWaja(Akar(P).name, g_win);
        // int j = 1;
        // while (j < Akar(P).name.Length && Akar(P).name.TabKata[j] != '\0')
        // {
        //     wprintw(g_win, "%c", Akar(P).name.TabKata[j]);
        //     j++;
        // }
        wprintw(g_win, "\n");
        if (!IsTreeEmpty(Left(P)))
        {
            for (i = 1; i <= h + idt; i++)
            {
                wprintw(g_win, " ");
            }
            PrintTreeWithIndentt(Left(P), h, idt + h);
        }
        if (!IsTreeEmpty(Right(P)))
        {
            for (i = 1; i <= h + idt; i++)
            {
                wprintw(g_win, " ");
            }
            PrintTreeWithIndentt(Right(P), h, idt + h);
        }
    }
}

void PrintTreee(BinTree P, int h)
{
    PrintTreeWithIndentt(P, h, 0);
}

void Print_RoomW(Matrix M)
/* Print Map ke layar. */
{
    int i, j;
    wprintw(g_win, "\n\n");
    for (i = MIN_ROW_MAP; i <= NRowEff(M); ++i)
    {

        for (j = MIN_COL_MAP; j <= NColEff(M); ++j)
        {
            if (j == 1)
                wprintw(g_win, "\t");
            if (ElmtMx(M, (i - 1), j).tag == TABLE)
                if (IsOccupied(ElmtMx(M, (i - 1), j)))
                {
                    wprintw(g_win, "C");
                }
                else
                {
                    wprintw(g_win, "X");
                }
            else if (ElmtMx(M, (i + 1), j).tag == TABLE)
                if (IsOccupied(ElmtMx(M, (i + 1), j)))
                {
                    if (Amount(CustomerAt(ElmtMx(M, (i + 1), j))) >= 2)
                    {
                        wprintw(g_win, "C");
                    }
                    else
                    {
                        wprintw(g_win, "X");
                    }
                }
                else
                {
                    wprintw(g_win, "X");
                }
            else if (ElmtMx(M, i, (j + 1)).tag == TABLE)
            {
                if (ElmtMx(M, i, (j + 1)).data.table.size != 2)
                    if (IsOccupied(ElmtMx(M, (i), j + 1)))
                    {
                        if (Amount(CustomerAt(ElmtMx(M, (i), j + 1))) >= 3)
                        {
                            wprintw(g_win, "C");
                        }
                        else
                        {
                            wprintw(g_win, "X");
                        }
                    }
                    else
                    {
                        wprintw(g_win, "X");
                    }
                else if (ElmtMx(M, i, j).tag == PLAYER_POS)
                {
                    wprintw(g_win, "P");
                }
                else
                    wprintw(g_win, "-");
            }
            else if (ElmtMx(M, i, (j - 1)).tag == TABLE)
            {
                if (ElmtMx(M, i, (j - 1)).data.table.size != 2)
                    if (IsOccupied(ElmtMx(M, (i), j - 1)))
                    {
                        if (Amount(CustomerAt(ElmtMx(M, (i), j - 1))) == 4)
                        {
                            wprintw(g_win, "C");
                        }
                        else
                        {
                            wprintw(g_win, "X");
                        }
                    }
                    else
                    {
                        wprintw(g_win, "X");
                    }
                else if (ElmtMx(M, i, j).tag == PLAYER_POS)
                {
                    wprintw(g_win, "P");
                }
                else
                    wprintw(g_win, "-");
            }
            else if (ElmtMx(M, i, j).tag == TABLE)
            {
                wprintw(g_win, "%d", ElmtMx(M, i, j).data.table.num);
            }
            else if (ElmtMx(M, i, j).tag == PLAYER_POS)
            {
                wprintw(g_win, "P");
            }
            else if (ElmtMx(M, i, j).tag == STOVE)
            {
                wprintw(g_win, "M");
            }
            else if (ElmtMx(M, i, j).tag == TRAY)
            {
                wprintw(g_win, "T");
            }
            else
            {
                wprintw(g_win, "-");
            }
            if (j != NColEff(M))
            {
                if (ElmtMx(M, i, j).tag == TABLE)
                {
                    if (TableNumber(ElmtMx(M, i, j)) / 10 == 0) //Kalau panjang angka > 2, maka dia langsung dikurangi dengan 1 space
                        wprintw(g_win, "    ");
                    else
                        wprintw(g_win, "   ");
                }
                else
                {
                    wprintw(g_win, "    ");
                }
            }
        }
        if (i != NRowEff(M))
            wprintw(g_win, "\n\n\n");
    }
}