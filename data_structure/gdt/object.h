/* *** GAME OBJECTS *** */
#define Tag(O)   (O).tag

    /* *** Table *** */
    #define CapacityOf(O)   (O).size
    #define IsOccupied(O)   (O).isFull
    #define OrdersAt(O)     (O).order
    #define CustomerAt(O)   (*((O).who))

    /* *** Stove *** */
    #define ItemsIn(O) (O).item

typedef struct {
  //unsigned short tag;
  gameObj tag;

  union {
    /* *** Table *** */
    struct {
      unsigned short num;
      unsigned short size;
      boolean isFull;
      customer_ptr who;
    } table;

    /* *** Stove *** */
    struct {
      IdType itemId;
    } stove;

  } data;

} Object;