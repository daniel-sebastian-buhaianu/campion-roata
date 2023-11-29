#include <fstream>
#include <algorithm>
#define NR_MAXIM_CABINE 360
#define NR_MAXIM_ROTATII 100000
#define NR_MAXIM_CLIENTI 100000
using namespace std;
struct Client { int nrOrdine, nrRotiri; };
struct Cabina { int nrOrdine; Client client; };
void citesteDateleDeIntrare(
	int & nrCabine,
	int & nrClienti,
	int & nrClientiLaCoada,
	int & sumaIncasata,
	Cabina cabine[],
	Client coadaClienti[]);
bool compar(Cabina, Cabina);
int main()
{
	int nrCabine,
	    nrClienti,
	    nrClientiLaCoada,
	    sumaIncasata;
	Cabina cabine[NR_MAXIM_CABINE+1];
	Client coadaClienti[NR_MAXIM_CLIENTI+1];
	citesteDateleDeIntrare(
		nrCabine,
		nrClienti,
		nrClientiLaCoada,
		sumaIncasata,
		cabine,
		coadaClienti);
	ofstream scrie("roata.out");
	scrie << sumaIncasata << endl;
	sort(cabine + 1, cabine + nrCabine + 1, compar);
	int i;
	for (i = 1; i <= nrClientiLaCoada; i++)
	{
		int rotiriEfectuate = cabine[nrCabine].client.nrRotiri;
		for (int j = 1; j <= nrCabine; j++)
		{
			cabine[j].client.nrRotiri
				-= rotiriEfectuate;
		}
		scrie << cabine[nrCabine].client.nrOrdine << ' ';
		cabine[nrCabine].client = coadaClienti[i];
		sort(cabine + 1, cabine + nrCabine + 1, compar);
	}
	for (i = nrCabine; i >= 1; i--)
	{
		scrie << cabine[i].client.nrOrdine << ' ';
	}
	scrie << endl << cabine[1].nrOrdine;
	scrie.close();
	return 0;
}
bool compar(Cabina a, Cabina b)
{
	if (a.client.nrRotiri > b.client.nrRotiri)
	{
		return 1;
	}
	if (a.client.nrRotiri == b.client.nrRotiri
		&& a.nrOrdine > b.nrOrdine)
	{
			return 1;
	}
	return 0;
}
void citesteDateleDeIntrare(
	int & nrCabine,
	int & nrClienti,
	int & nrClientiLaCoada,
	int & sumaIncasata,
	Cabina cabine[],
	Client coadaClienti[])
{
	ifstream citeste("roata.in");
	citeste >> nrCabine >> nrClienti;
	int i;
	for (sumaIncasata = 0, i = 1;
	     i <= nrCabine && i <= nrClienti; i++)
	{
		citeste >> cabine[i].client.nrRotiri;
		sumaIncasata += cabine[i].client.nrRotiri;
		cabine[i].nrOrdine = i;
		cabine[i].client.nrOrdine = i;
	}
	for (nrClientiLaCoada = 0; i <= nrClienti; i++)
	{
		Client client;
		citeste >> client.nrRotiri;
		sumaIncasata += client.nrRotiri;
		client.nrOrdine = i;
		coadaClienti[++nrClientiLaCoada] = client;
	}
	citeste.close();
}
