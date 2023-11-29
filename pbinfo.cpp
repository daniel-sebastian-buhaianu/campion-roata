#include <fstream>
#include <algorithm>
#define NR_MAXIM_CABINE 360
#define NR_MAXIM_ROTATII 100000
#define NR_MAXIM_CLIENTI 100000
using namespace std;
struct Client { int nrOrdine; unsigned long long nrRotiri; };
struct Cabina { int nrOrdine; Client client; };
void citesteDateleDeIntrare(
	int & nrCabine,
	int & nrClienti,
	int & nrClientiLaCoada,
	unsigned long long & sumaIncasata,
	Cabina cabine[],
	Client coadaClienti[]);
bool compar(Cabina, Cabina);
int pozitieCabina(
	Cabina urmatoareaCabinaLibera,
	Client urmatorulClient,
	Cabina cabine[],
	int nrCabine);
int main()
{
	int nrCabine,
	    nrClienti,
	    nrClientiLaCoada;
	unsigned long long sumaIncasata;
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
		Cabina urmatoareaCabinaLibera;
		urmatoareaCabinaLibera.nrOrdine
			= cabine[nrCabine].nrOrdine;
		urmatoareaCabinaLibera.client
			= cabine[nrCabine].client;
		scrie << urmatoareaCabinaLibera
				.client
				.nrOrdine << ' ';
		Client urmatorulClient = coadaClienti[i];
		urmatorulClient.nrRotiri += urmatoareaCabinaLibera
						.client
						.nrRotiri;
		int pozitie = pozitieCabina(
				urmatoareaCabinaLibera,
				urmatorulClient,
				cabine,
				nrCabine);
		for (int j = nrCabine; j > pozitie; j--)
		{
			cabine[j] = cabine[j-1];
		}
		urmatoareaCabinaLibera.client = urmatorulClient;
		cabine[pozitie] = urmatoareaCabinaLibera;
	}
	for (i = nrCabine; i >= 1; i--)
	{
		scrie << cabine[i].client.nrOrdine << ' ';
	}
	scrie << endl << cabine[1].nrOrdine;
	scrie.close();
	return 0;
}
int pozitieCabina(
	Cabina urmatoareaCabinaLibera,
	Client urmatorulClient,
	Cabina cabine[],
	int nrCabine)
{
	// folosesc cautare binara pentru a gasi
	// pozitia cabinei urmatorului client 
	// in vectorul de cabine sortat descrescator
	int stanga = 0,
	    dreapta = nrCabine + 1;
	while (dreapta - stanga > 1)
	{
		int mijloc = stanga
			     + (dreapta - stanga)/2;
		int cabinaMijloc = cabine[mijloc].nrOrdine;
		unsigned long long
			nrRotiriCabinaMijloc = cabine[mijloc]
						.client
						.nrRotiri;
		if (nrRotiriCabinaMijloc > urmatorulClient.nrRotiri
		    || (nrRotiriCabinaMijloc == urmatorulClient.nrRotiri
		        && cabinaMijloc > urmatoareaCabinaLibera.nrOrdine))
		{
			stanga = mijloc;
		}
		else
		{
			dreapta = mijloc;
		}
	}
	return dreapta;
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
	unsigned long long & sumaIncasata,
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
		cabine[i].nrOrdine = i;
		cabine[i].client.nrOrdine = i;
		sumaIncasata += cabine[i].client.nrRotiri;
	}
	for (nrClientiLaCoada = 0; i <= nrClienti; i++)
	{
		Client client;
		citeste >> client.nrRotiri;
		client.nrOrdine = i;
		coadaClienti[++nrClientiLaCoada] = client;
		sumaIncasata += client.nrRotiri;
	}
	if (nrCabine > nrClienti)
	{
		nrCabine = nrClienti;
	}
	citeste.close();
}

