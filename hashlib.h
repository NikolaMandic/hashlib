union{
  float f;
  int i;
}u;
#define L 100
typedef struct {
 void * val;
}Dict;

typedef struct DictM{
 int key;
 void * val;
}DictM;

typedef struct DictMLL{
 int key;
 void * val;
 void * next;
}DictMLL;

int hash(int key,int length)
int dict_storell(struct DictMLL *d,int(*h)(int,int),int key,void * val,int len)
void * dict_getll(struct DictMLL *d,int(*h)(int,int),int key,int len)

int dict_store(Dict *d,int(*h)(int,int),int key,void * val,int len)
int dictm_store(DictM *d,int(*h)(int,int),int key,void * val,int len)
int dict_storell(struct DictMLL *d,int(*h)(int,int),int key,void * val,int len)

typedef struct ll ll;
typedef struct ll{
  void *val;
  int key;
  ll * next;
}ll;
