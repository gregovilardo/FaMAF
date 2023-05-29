long long int i = 50;
long long int *MemArray;
long long int result;
long long int a;
int main() {
while(i != 0) {
  a = MemArray[0];
  result += a;
  a = MemArray[1];
  result += a;
  MemArray=MemArray+16;
  i--;
}
  return 0;
}
