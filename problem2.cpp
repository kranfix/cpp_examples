#include <iostream>
#include <string>
#include <iomanip>
#include <stdio.h>

using namespace std;

class PuntoEspacial
{
public:
  int x, y, z;
  PuntoEspacial(int x, int y, int z) : x(x), y(y), z(z) {}
  PuntoEspacial() : x(0), y(0), z(0) {}

  void display()
  {
    cout << toString() << endl;
  }

  bool operator==(PuntoEspacial otro)
  {
    return x == otro.x && y == otro.y && z == otro.z;
  }

  std::string toString()
  {
    char text[80];
    sprintf(text, "PuntoEspacial(%d, %d, %d)", x, y, z);
    return std::string(text);
  }
};

class PuntoColoreado : public PuntoEspacial
{
public:
  PuntoColoreado(int r, int g, int b) : PuntoEspacial(r, g, b)
  {
  }

  PuntoColoreado(int hexValue) : PuntoEspacial(hexValue >> 16 & 0xFF, hexValue >> 8 & 0xFF, hexValue & 0xFF)
  {
  }

  void display()
  {
    cout << "PuntoColoreado(#"
         << uppercase << hex << std::setfill('0') << setw(2)
         << x << y << z << ")" << endl;
  }
};

class AdminPuntos
{
protected:
  int _capacity;
  int _length;

public:
  PuntoEspacial *puntos;

  AdminPuntos(PuntoEspacial puntos[], int length, int capacity = 0) : puntos(puntos), _length(length), _capacity(capacity > length ? capacity : length) {}

  int length()
  {
    return _length;
  }

  int capacity()
  {
    return _capacity;
  }

  bool insertar(PuntoEspacial nuevo)
  {
    if (_length < _capacity)
    {
      puntos[_length] = nuevo;
      _length++;
      return true;
    }
    return false;
  }

  int buscarPosi(PuntoEspacial buscado, int offset = 0)
  {
    for (int pos = offset; pos < _length; pos++)
    {
      if (puntos[pos] == buscado)
      {
        return pos;
      }
    }
    return -1;
  }

  PuntoEspacial leer(int posi)
  {
    return puntos[posi];
  }

  void ordenarZ()
  {
    for (int i = _length - 1; i >= 1; i--)
    {
      for (int j = 0; j < i; j++)
      {
        if (puntos[j + 1].z < puntos[j].z)
        {
          swap(j, j + 1);
        }
      }
    }
  }

  bool eliminar(PuntoEspacial borrado)
  {
    int pos = buscarPosi(borrado);
    if (pos == -1)
      return false;
    eliminar(pos);
    return true;
  }

  void eliminar(int posi)
  {
    if (posi < 0 || posi >= _length)
      return;

    _length--;
    for (int i = posi; i < _length; i++)
    {
      puntos[i] = puntos[i + 1];
    }
  }

  void eliminarZ(int z)
  {
    int length = 0;
    for (int i = 0; i < _length; i++)
    {
      auto punto = puntos[i];
      puntos[length] = punto;
      if (punto.z != z)
      {
        length++;
      }
    }
    _length = length;
  }

protected:
  void swap(int i, int j)
  {
    auto temporal = puntos[i];
    puntos[i] = puntos[j];
    puntos[j] = temporal;
  }
};

class MultiAdmin : public AdminPuntos
{
public:
  MultiAdmin(PuntoEspacial *puntos, int lenght, int capacity = 0) : AdminPuntos(puntos, lenght, capacity) {}

  void ImprimirTodos()
  {
    cout << "MultiAdmin (length: "
         << _length << ", capacity: " << _capacity << ") :" << endl;
    for (int i = 0; i < _length; i++)
    {
      cout << "  - " << puntos[i].toString() << endl;
    }
    cout << endl;
  }

  void eliminarX(int x)
  {
    int length = 0;
    for (int i = 0; i < _length; i++)
    {
      auto punto = puntos[i];
      puntos[length] = punto;
      if (punto.x != x)
      {
        length++;
      }
    }
    _length = length;
  }
};

int main()
{
  auto spacialPoint = PuntoEspacial(1, 2, 3);
  spacialPoint.display();

  auto colorPoint = PuntoColoreado(200, 10, 120);
  colorPoint.display();

  PuntoEspacial puntos[6] = {
      PuntoEspacial(20, 2, 3),
      PuntoEspacial(1, 4, 5),
      colorPoint,
      PuntoEspacial(9, 3, 4),
      //PuntoEspacial(),
      //PuntoEspacial(),
  };

  auto adminPuntos = MultiAdmin(puntos, 4, 6);
  adminPuntos.ImprimirTodos();
  adminPuntos.insertar(PuntoEspacial(2, 3, 5));
  adminPuntos.insertar(PuntoEspacial(20, 1, 1));
  adminPuntos.ImprimirTodos();
  adminPuntos.ordenarZ();
  adminPuntos.ImprimirTodos();
  adminPuntos.eliminarZ(5);
  adminPuntos.ImprimirTodos();
  adminPuntos.eliminarX(20);
  adminPuntos.ImprimirTodos();
}
