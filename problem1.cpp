#include <iostream>
#include <vector>

using namespace std;

vector<int> find(vector<int> a, int n, int s)
{
  for (int i = 0; i < n; i++)
  {
    int sum = 0;
    for (vector<int>::iterator it = a.begin() + i; it != a.end(); it++)
    {
      sum += *it;
      if (sum == s)
      {
        return {i, (int)(it - a.begin())};
      }
    }
  }
  return a;
}

int main()
{
  //code
  int s, n, no;
  cout << "enter array length & Sum respectively" << endl;
  scanf("%d%d", &n, &s);
  vector<int> a; //input array
  cout << "enter array elements........" << endl;
  for (int j = 0; j < n; j++)
  {
    scanf("%d", &no);
    a.push_back(no); //inserting array elements
  }
  vector<int> b = find(a, n, s);
  if (b[0] == -1)
    printf("subarray not found");
  else
  {
    cout << "Subarray is: ";
    for (int i = b[0]; i <= b[1]; i++)
      cout << a[i] << " ";
    cout << endl;
  }
  return 0;
}