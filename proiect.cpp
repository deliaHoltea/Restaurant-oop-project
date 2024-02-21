#include<iostream>
#include <fstream>
#include<string>
#include <vector>
#include<list>
#include<set>
using namespace std;

class IFisier {
	virtual void scrieFisierBin(fstream& file) = 0;
	virtual void citesteFisierBin(fstream& file) = 0;
};
enum ValoriNutritionale {
	PROTEINE, CALORII, CARBOHIDRATI
};

class MateriePrima:public IFisier{
private:
	char* denumire=nullptr;
	double stoc=0.00;
public:
	MateriePrima() {
		this->denumire = new char[strlen("Necunoscuta") + 1];
		strcpy_s(this->denumire, strlen("Necunoscuta") + 1, "Necunoscuta");
	}
	MateriePrima(const char* denumire, double stoc){
		if (denumire != nullptr && strlen(denumire) > 1) {
			this->denumire = new char[strlen(denumire) + 1];
			strcpy_s(this->denumire, strlen(denumire) + 1, denumire);
		}
		else {
			this->denumire = new char[strlen("Necunoscuta") + 1];
			strcpy_s(this->denumire, strlen("Necunoscuta") + 1, "Necunoscuta");
		}
		if (stoc > 0)
			this->stoc = stoc;

	}
	MateriePrima(const MateriePrima& m) {
		if (m.denumire != nullptr&&strlen(m.denumire)>0) {
			this->denumire = new char[strlen(m.denumire) + 1];
			strcpy_s(this->denumire, strlen(m.denumire) + 1, m.denumire);
		}
		else {
			this->denumire = new char[strlen("Necunoscuta") + 1];
			strcpy_s(this->denumire, strlen("Necunoscuta") + 1, "Necunoscuta");
		}
		if (m.stoc > 0)
			this->stoc = m.stoc;
	}
	~MateriePrima() {
		delete[] this->denumire;
		this->denumire = nullptr;
	}

	void setDenumireMateriePrima(const char* denumire) {
		if (denumire != nullptr && strlen(denumire) > 1) {
			this->denumire = new char[strlen(denumire) + 1];
			strcpy_s(this->denumire, strlen(denumire) + 1, denumire);
		}
	}
	void setStocMateriePrima(double stoc) {
		if (stoc > 0)
			this->stoc = stoc;
	}

	const char* getDenumireMateriePrima() {
		return this->denumire;
	}
	double getStocMateriePrima() {
		return this->stoc;
	}

	friend ostream& operator<<(ostream& out, const MateriePrima& m)
	{
		out << "\n----MATERIE PRIMA----";
		out << "\nDenumire: "<<m.denumire;
		out << "\nStoc: " << m.stoc;
		return out;
		
	}
	friend istream& operator>>(istream& in, MateriePrima& m) {
		cout << "\nIntroduceti denumire: " ;
		string buffer;
		in>>buffer;
		if (buffer != "") {
			delete[] m.denumire;
			m.denumire = new char[buffer.length() + 1];
			strcpy_s(m.denumire, buffer.length() + 1, buffer.data());
		}
		else{
			m.denumire = new char[strlen("Necunoscuta") + 1];
			strcpy_s(m.denumire, strlen("Necunoscuta") + 1, "Necunoscuta");
		}
		cout << "\nIntroduceti stocul: ";
		in >> m.stoc;
		if (m.stoc < 0)
			m.stoc = 0;
		return in;
	}
	MateriePrima& operator=(const MateriePrima& m) {
		if (this != &m) {
			delete[] this->denumire;
			this->denumire = nullptr;

			if (m.denumire != nullptr && strlen(m.denumire) > 0) {
				this->denumire = new char[strlen(m.denumire) + 1];
				strcpy_s(this->denumire, strlen(m.denumire) + 1, m.denumire);
			}
			else {
				this->denumire = new char[strlen("Necunoscuta") + 1];
				strcpy_s(this->denumire, strlen("Necunoscuta") + 1, "Necunoscuta");
			}
			if(m.stoc>0)
			this->stoc = m.stoc;
		}
		return *this;
	}
	MateriePrima& operator --() {
		this->stoc--;
		return *this;
	}
	MateriePrima& operator--(int) {
		MateriePrima copie = *this;
		this->stoc--;
		return copie;
	}
	bool operator!=(int nr) {
		if (nr == 0) {
			if (strcmp(this->denumire, "Necunoscuta") != 0)
				return true;
			if (this->stoc != 0)
				return true;
			return false;
		}
		else
		{
			if (this->stoc != nr)
				return true;
			return false;
		}
	}
	MateriePrima& operator -(float nr) {
		this->stoc = this->stoc - nr;
		return *this;
	}
	//pt faza 2
	friend ifstream& operator>>(ifstream& input, MateriePrima& m) {
		string buffer;
		input >> buffer;
		delete[] m.denumire;
		m.denumire = new char[buffer.length() + 1];
		strcpy_s(m.denumire, buffer.length() + 1, buffer.data());
		input >> m.stoc;
		return input;
	}
	void scrieFisierBin(fstream& file) {
		int lungimeDenumire = strlen(denumire)+1;
		file.write((char*)&lungimeDenumire, sizeof(int));
		file.write(this->denumire, lungimeDenumire);
		file.write((char*)&this->stoc, sizeof(double));
	}
	void citesteFisierBin(fstream& file) {
		int lungimeDenumire;
		file.read((char*)&lungimeDenumire, sizeof(int));
		char* buff= new char[lungimeDenumire];
		file.read(buff, lungimeDenumire);
		strcpy_s(this->denumire, lungimeDenumire, buff);
		delete[] buff;
		file.read((char*)&this->stoc, sizeof(double));
	}
	friend bool operator<(const MateriePrima& m1, const MateriePrima &m2) {
		string buff1 = m1.denumire;
		string buff2 = m2.denumire;
		return buff1 < buff2;
	}
};

class Retetar:public IFisier {
private:
	int nrMateriiPrime = 0;
	MateriePrima* materiePrima = nullptr;
	float* cantitateMateriePrima = nullptr;
	float timpPregatire = 0.00;
	static MateriePrima* stoc;
	static int nrIngredienteStoc;

public:
	Retetar() {
		this->nrMateriiPrime = 0;
		this->materiePrima = nullptr;
		this->cantitateMateriePrima = nullptr;
		this->timpPregatire = 0.00;
	}
	Retetar(int nrMateriiPrime, MateriePrima* materiePrima, float* cantitateMateriePrima, float timpPregatire) {
		if (nrMateriiPrime > 0) 
			this->nrMateriiPrime = nrMateriiPrime;
		if (materiePrima != nullptr && nrMateriiPrime > 0) {
			this->materiePrima = new MateriePrima[nrMateriiPrime];
			for (int i = 0; i < this->nrMateriiPrime; i++)
				if (materiePrima[i] != 0)
					this->materiePrima[i] = materiePrima[i];

		}
		else {
			this->nrMateriiPrime = 0;
			this->materiePrima = nullptr;
		}
		if (cantitateMateriePrima != nullptr && nrMateriiPrime > 0) {
			this->cantitateMateriePrima = new float[nrMateriiPrime];
				for (int i = 0; i < this->nrMateriiPrime; i++)
					if (cantitateMateriePrima[i] > 0)
						this->cantitateMateriePrima[i] = cantitateMateriePrima[i];
		}
		else {
			this->nrMateriiPrime = 0;
			this->cantitateMateriePrima = 0;
		}
		if (timpPregatire > 0)
			this->timpPregatire = timpPregatire;
	}
	Retetar(const Retetar& r) {
		if (nrMateriiPrime > 0)
			this->nrMateriiPrime = r.nrMateriiPrime;
		if (r.materiePrima != nullptr && r.nrMateriiPrime > 0) {
			this->nrMateriiPrime = r.nrMateriiPrime;
			this->materiePrima = new MateriePrima[r.nrMateriiPrime];
			for (int i = 0; i < this->nrMateriiPrime; i++)
				if (r.materiePrima[i] != 0)
					this->materiePrima[i] = r.materiePrima[i];
		}
		else {
			this->nrMateriiPrime = 0;
			this->materiePrima = nullptr;
		}
		if (r.cantitateMateriePrima != nullptr && r.nrMateriiPrime > 0) {
			this->cantitateMateriePrima = new float[r.nrMateriiPrime];
			for (int i = 0; i < this->nrMateriiPrime; i++)
				if (r.cantitateMateriePrima[i] > 0)
					this->cantitateMateriePrima[i] = r.cantitateMateriePrima[i];
		}
		else {
			this->nrMateriiPrime = 0;
			this->cantitateMateriePrima = nullptr;
		}
		if (r.timpPregatire > 0)
			this->timpPregatire = r.timpPregatire;
	}
	~Retetar() {
		delete[] this->materiePrima;
		delete[] this->cantitateMateriePrima;
		this->materiePrima = nullptr;
		this->cantitateMateriePrima = nullptr;
	}
	
	void setNrMateriiPrime(int nr) {
		if (nr > 0)
			this->nrMateriiPrime = nr;
	}
	void setMateriePrima(MateriePrima* materiePrima) {
		if (materiePrima != nullptr) {
			this->nrMateriiPrime = sizeof(materiePrima) / sizeof(float);
			delete[] this->materiePrima;
			this->materiePrima = new MateriePrima[this->nrMateriiPrime];
			for (int i = 0; i < this->nrMateriiPrime; i++)
				if (materiePrima[i] != 0)
					this->materiePrima[i] = materiePrima[i];

		}
	}
	void setCantitateMateriePrima(float* cantitateMateriePrima) {
		if (cantitateMateriePrima != nullptr) {
			this->nrMateriiPrime = sizeof(cantitateMateriePrima) / sizeof(float);
			delete[] this->cantitateMateriePrima;
			this->cantitateMateriePrima = new float[this->nrMateriiPrime];
			for (int i = 0; i < this->nrMateriiPrime; i++)
				if (cantitateMateriePrima[i] > 0)
					this->cantitateMateriePrima[i] = cantitateMateriePrima[i];
		}
	}
	void setTimpPregatire(float timpPregatire) {
		if (timpPregatire > 0)
			this->timpPregatire = timpPregatire;
	}
	void setIngrediente(MateriePrima* materiePrima, float* cantitateMateriePrima, int nrIngrediente) {
		if (nrIngrediente > 0) {
			this->nrMateriiPrime = nrIngrediente;

			if (materiePrima != nullptr) {
				this->nrMateriiPrime = nrIngrediente;
				delete[] this->materiePrima;
				this->materiePrima = new MateriePrima[this->nrMateriiPrime];
				for (int i = 0; i < this->nrMateriiPrime; i++)
					if (materiePrima[i] != 0)
						this->materiePrima[i] = materiePrima[i];
			}

			if (cantitateMateriePrima != nullptr) {
				this->nrMateriiPrime = nrIngrediente;
				delete[] this->cantitateMateriePrima;
				this->cantitateMateriePrima = new float[this->nrMateriiPrime];
				for (int i = 0; i < this->nrMateriiPrime; i++)
					if (cantitateMateriePrima[i] > 0)
						this->cantitateMateriePrima[i] = cantitateMateriePrima[i];
			}
		}
	}
	
	const MateriePrima* getMateriePrima() {
		return this->materiePrima;
	}
	const float* getCantitateMateriePrima() {
		return this->cantitateMateriePrima;
	}
	float getTimpPregatire() {
		return this->timpPregatire;
	}
	int getNrMateriiPrime() {
		return this->nrMateriiPrime;
	}

	static const MateriePrima* getStoc () {
		return Retetar::stoc;
	}
	static const int getNrIngredienteStoc() {
		return Retetar::nrIngredienteStoc;
	}
	static void setStoc(MateriePrima* stoc, int nr) {
		if (stoc != nullptr && nr > 0) {
			delete[] Retetar::stoc;
			Retetar::stoc = new MateriePrima[nr];
			Retetar::nrIngredienteStoc = nr;
			for (int i = 0; i < nr; i++)
				if (stoc[i] != 0)
					Retetar::stoc[i] = stoc[i];
		}
	}
	static MateriePrima* gasesteIngredient(string denumire) {
		for (int i = 0; i < Retetar::nrIngredienteStoc; i++)
			if (strcmp(denumire.data(), Retetar::stoc[i].getDenumireMateriePrima()) == 0)
				return &Retetar::stoc[i];
		return nullptr;
	}
	static void adaugaIngredient(const MateriePrima& ingredient) {
		if (&ingredient) {
			MateriePrima* copie = new MateriePrima[Retetar::nrIngredienteStoc];
			for (int i = 0; i < Retetar::nrIngredienteStoc; i++)
				copie[i] = Retetar::stoc[i];
			delete[] Retetar::stoc;
			Retetar::nrIngredienteStoc++;
			Retetar::stoc = new MateriePrima[Retetar::nrIngredienteStoc];
			for (int i = 0; i < Retetar::nrIngredienteStoc - 1; i++)
				Retetar::stoc[i] = copie[i];
			Retetar::stoc[Retetar::nrIngredienteStoc - 1] = ingredient;
			delete[] copie;
		}
	}
	static void afisareStoc() {
		for (int i = 0; i < Retetar::nrIngredienteStoc; i++)
			cout << Retetar::stoc[i];
	}
	static void scadeStoc(string denumire, float cantitate) {
		if(denumire!=""&& cantitate>0){
			for (int i = 0; i < nrIngredienteStoc; ++i) {
				if (denumire == stoc[i].getDenumireMateriePrima()) {
					stoc[i] - cantitate;
					break;
				}
			}
		}
	}

	bool confirmareComanda() {
		for (int i = 0; i < this->nrMateriiPrime; i++) {
			MateriePrima aux = *Retetar::gasesteIngredient(this->materiePrima[i].getDenumireMateriePrima());
			if (aux.getStocMateriePrima() < cantitateMateriePrima[i])
				return false;
		}
			return true;
	}
	void afisareDenumiri() {
		if (this->materiePrima != nullptr && this->nrMateriiPrime > 0) {
			for (int i = 0; i < this->nrMateriiPrime-1; i++)
				cout << this->materiePrima[i].getDenumireMateriePrima() << ", ";
			cout << this->materiePrima[this->nrMateriiPrime - 1].getDenumireMateriePrima();
		}
	}
	void lansareComanda() {
		for (int i = 0; i < this->nrMateriiPrime; ++i) {
			const char* denumire = this->materiePrima[i].getDenumireMateriePrima();
			float stoc = this->cantitateMateriePrima[i];
			Retetar::scadeStoc(denumire, stoc);
		}
	}

	friend ostream& operator<<(ostream& out, const Retetar& r) {
		out << "\n----Retetar----";
		out << "\nNumar ingrediente: " << r.nrMateriiPrime;
		if (r.nrMateriiPrime > 0) {
			if (r.materiePrima != nullptr) {
				out << "\nIngrediente: ";
				for (int i = 0; i < r.nrMateriiPrime - 1; i++)
					out << r.materiePrima[i].getDenumireMateriePrima() << ", ";
				out << r.materiePrima[r.nrMateriiPrime - 1].getDenumireMateriePrima();
			}
			if (r.cantitateMateriePrima != nullptr) {
				out << "\nCantitati ingrediente: ";
				for (int i = 0; i < r.nrMateriiPrime - 1; i++)
					out << r.cantitateMateriePrima[i] << ", ";
				out << r.cantitateMateriePrima[r.nrMateriiPrime - 1];
			}
		}
		out << "\nTimp pregatire: " << r.timpPregatire;
		out << "\n---------------";
		return out;
	}
	friend istream& operator>>(istream& in, Retetar& r) {
		cout << "\nIntroduceti numarul ingredientelor: ";
		in >> r.nrMateriiPrime;
		if (r.nrMateriiPrime < 0)
			r.nrMateriiPrime = 0;

		if (r.nrMateriiPrime > 0) {
			delete[] r.materiePrima;
			delete[] r.cantitateMateriePrima;
			r.materiePrima = new MateriePrima[r.nrMateriiPrime];
			r.cantitateMateriePrima = new float[r.nrMateriiPrime];

			for (int i = 0; i < r.nrMateriiPrime; i++) {
				cout << "\nIntroduceti nume inngredient " << i + 1 << " : ";
				string buff;
				in >> buff;
				if (Retetar::gasesteIngredient(buff) != nullptr) {
					r.materiePrima[i] = *Retetar::gasesteIngredient(buff);
					cout << "\nIntroduceti cantitate ingredient " << r.materiePrima[i].getDenumireMateriePrima() << ": ";
					in >> r.cantitateMateriePrima[i];
				}
				else {
					r.materiePrima[i] = MateriePrima();
					r.cantitateMateriePrima[i] = 0;
				}
			}
		}

		cout << "\nIntroduceti timpul de pregatire: ";
		in >> r.timpPregatire;
		if (r.timpPregatire < 0)
			r.timpPregatire = 0;
		return in;
	}
	Retetar& operator=(const Retetar& r) {
		if (this != &r) {
			delete[] this->materiePrima;
			delete[] this->cantitateMateriePrima;
			this->materiePrima = nullptr;
			this->cantitateMateriePrima = nullptr;

			if (nrMateriiPrime > 0)
				this->nrMateriiPrime = r.nrMateriiPrime;
			if (r.materiePrima != nullptr && r.nrMateriiPrime > 0) {
				this->nrMateriiPrime = r.nrMateriiPrime;
				this->materiePrima = new MateriePrima[r.nrMateriiPrime];
				for (int i = 0; i < this->nrMateriiPrime; i++)
					if (r.materiePrima[i] != 0)
						this->materiePrima[i] = r.materiePrima[i];
			}
			else {
				this->nrMateriiPrime = 0;
				this->materiePrima = nullptr;
			}
			if (r.cantitateMateriePrima != nullptr && r.nrMateriiPrime > 0) {
				this->cantitateMateriePrima = new float[r.nrMateriiPrime];
				for (int i = 0; i < this->nrMateriiPrime; i++)
					if (r.cantitateMateriePrima[i] > 0)
						this->cantitateMateriePrima[i] = r.cantitateMateriePrima[i];
			}
			else {
				this->nrMateriiPrime = 0;
				this->cantitateMateriePrima = nullptr;
			}
			if (r.timpPregatire > 0)
				this->timpPregatire = r.timpPregatire;
		}
		return *this;
	}
	float operator[](int index) {
		for (int i = 0; i < this->nrMateriiPrime; i++)
			if (cantitateMateriePrima[i] == cantitateMateriePrima[index])
				return cantitateMateriePrima[i];
	}
	bool operator!=(const Retetar& r) const {
		if (this->nrMateriiPrime != r.nrMateriiPrime)
			return true;
		if ((this->materiePrima == nullptr && r.materiePrima != nullptr) ||
			(this->materiePrima != nullptr && r.materiePrima == nullptr))
			return true;
		if ((this->cantitateMateriePrima == nullptr && r.cantitateMateriePrima != nullptr) ||
			(this->cantitateMateriePrima != nullptr && r.cantitateMateriePrima == nullptr))
			return true;
		if (this->timpPregatire != r.timpPregatire)
			return true;
		return false;
	}
	//pt faza 2
	friend ifstream& operator>>(ifstream& in, Retetar& r) {
		in >> r.nrMateriiPrime;
		if (r.nrMateriiPrime < 0)
			r.nrMateriiPrime = 0;

		if (r.nrMateriiPrime > 0) {
			delete[] r.materiePrima;
			delete[] r.cantitateMateriePrima;
			r.materiePrima = new MateriePrima[r.nrMateriiPrime];
			r.cantitateMateriePrima = new float[r.nrMateriiPrime];

			for (int i = 0; i < r.nrMateriiPrime; i++) {
				string buff;
				in >> buff;
				if (Retetar::gasesteIngredient(buff) != nullptr) {
					r.materiePrima[i] = *Retetar::gasesteIngredient(buff);
					in >> r.cantitateMateriePrima[i];
				}
				else {
					r.materiePrima[i] = MateriePrima();
					r.cantitateMateriePrima[i] = 0;
				}
			}
		}
		in >> r.timpPregatire;
		if (r.timpPregatire < 0)
			r.timpPregatire = 0;
		return in;
	}

	void scrieFisierBin(fstream& file) {
		file.write((char*)&this->nrMateriiPrime, sizeof(int));
		for (int i = 0; i < this->nrMateriiPrime; i++)
			this->materiePrima[i].scrieFisierBin(file);
		for (int i = 0; i < this->nrMateriiPrime; i++)
			file.write((char*)&this->cantitateMateriePrima[i], sizeof(float));
		file.write((char*)&this->timpPregatire, sizeof(float));
	}
	void citesteFisierBin(fstream& file) {
		file.read((char*)&this->nrMateriiPrime, sizeof(int));

		delete[] this->materiePrima;
		delete[] this->cantitateMateriePrima;
		this->cantitateMateriePrima = new float[nrMateriiPrime];
		this->materiePrima = new MateriePrima[nrMateriiPrime];
		for (int i = 0; i < this->nrMateriiPrime; i++)
			this->materiePrima[i].citesteFisierBin(file);
		for (int i = 0; i < this->nrMateriiPrime; i++)
			file.read((char*)&this->cantitateMateriePrima[i], sizeof(float));
		file.read((char*)&this->timpPregatire, sizeof(float));
	}
};
MateriePrima* Retetar::stoc = nullptr;
int Retetar::nrIngredienteStoc = 0;

class Produs {
private:
	string denumire = "Necunoscuta";
	Retetar retetar = Retetar();
	float pret = 0.00;
	float cantitateProdus = 0.00;
	ValoriNutritionale* valoriNutritionale = nullptr;
	float* cantitateValoriNutritionale = nullptr;

public:
	Produs() {
		this->denumire = "Necunoscuta";
		this->retetar = Retetar();
		this->pret = 0.00;
		this->cantitateProdus = 0.00;
		this->valoriNutritionale = new ValoriNutritionale[3];
		this->valoriNutritionale[0] = ValoriNutritionale::CALORII;
		this->valoriNutritionale[1] = ValoriNutritionale::PROTEINE;
		this->valoriNutritionale[2] = ValoriNutritionale::CARBOHIDRATI;
		this->cantitateValoriNutritionale = new float[3];
		for (int i = 0; i < 3; i++)
			this->cantitateValoriNutritionale[i] = 0;
	}
	Produs(string denumire, Retetar retetar, float pret, float cantitate, float* cantitateValoriNutritionale) {
		if (denumire != "")
			this->denumire = denumire;
		this->retetar = retetar;
		if (pret > 0)
			this->pret = pret;
		if (cantitate > 0)
			this->cantitateProdus = cantitate;
		if (cantitateValoriNutritionale != nullptr) {
			this->valoriNutritionale = new ValoriNutritionale[3];
			this->valoriNutritionale[0] = ValoriNutritionale::CALORII;
			this->valoriNutritionale[1] = ValoriNutritionale::PROTEINE;
			this->valoriNutritionale[2] = ValoriNutritionale::CARBOHIDRATI;
			this->cantitateValoriNutritionale = new float[3];
			for (int i = 0; i < 3; i++) {
				if (cantitateValoriNutritionale[i] > 0)
					this->cantitateValoriNutritionale[i] = cantitateValoriNutritionale[i];
				else
					this->cantitateValoriNutritionale[i] = 0;
			}
		}
	}
	Produs(const Produs& p) {
		if (p.denumire != "")
			this->denumire = p.denumire;
		this->retetar = p.retetar;
		if (p.pret > 0)
			this->pret = p.pret;
		if (p.cantitateProdus > 0)
			this->cantitateProdus = p.cantitateProdus;
		if (p.valoriNutritionale != nullptr && p.cantitateValoriNutritionale != nullptr) {
			this->valoriNutritionale = new ValoriNutritionale[3];
			this->cantitateValoriNutritionale = new float[3];
			for (int i = 0; i < 3; i++) {
				this->valoriNutritionale[i] = p.valoriNutritionale[i];
				if (p.cantitateValoriNutritionale[i] > 0)
					this->cantitateValoriNutritionale[i] = p.cantitateValoriNutritionale[i];
				else
					this->cantitateValoriNutritionale[i] = 0;
			}
		}
	}
	~Produs() {
		delete[] this->valoriNutritionale;
		delete[] this->cantitateValoriNutritionale;
		this->cantitateValoriNutritionale = nullptr;
		this->cantitateValoriNutritionale = nullptr;
	}

	string getDenumireProdus() {
		return this->denumire;
	}
	const Retetar* getRetetar() {
		return &this->retetar;
	}
	float getPretProdus() {
		return this->pret;
	}
	float getCantitateProdus() {
		return this->cantitateProdus;
	}
	const ValoriNutritionale* getValoriNutritionale() {
		return this->valoriNutritionale;
	}
	const float* getCantitateValoriNutritionale() {
		return this->cantitateValoriNutritionale;
	}

	void setDenumireProdus(string denumire) {
		if (denumire != "")
			this->denumire = denumire;
	}
	void setRetetar(const Retetar& r) {
		this->retetar = r;
	}
	void setPretProdus(float pret) {
		if (pret > 0)
			this->pret = pret;
	}
	void setCantitateProdus(float cantitate) {
		if (cantitate > 0)
			this->cantitateProdus = cantitate;
	}
	void setValoriNutritionale(ValoriNutritionale* valoriNutritionale) {
		if (valoriNutritionale != nullptr && sizeof(valoriNutritionale) == 3 * sizeof(ValoriNutritionale)) {
			delete[] this->valoriNutritionale;
			this->valoriNutritionale = new ValoriNutritionale[3];
			this->valoriNutritionale = valoriNutritionale;
		}
	}
	void setCantitatiValoriNutritionale(float* cantitati) {
		if (cantitati != nullptr && sizeof(cantitati) == 3 * sizeof(float)) {
			delete[] this->cantitateValoriNutritionale;
			this->cantitateValoriNutritionale = new float[3];
			this->cantitateValoriNutritionale = cantitati;
		}
	}

	void afisareProdus() {
		cout << "\nDenumire: " << this->denumire;
		cout << "\nPret: " << this->pret << " lei";
		cout << "\nIngrediente: ";
		this->retetar.afisareDenumiri();
		cout << "\nCantitate: " << this->cantitateProdus << " g";

	}
	void afisareTimpPregatire() {
		cout<<this->retetar.getTimpPregatire()<<" min";
	}
	bool confirmareComandaProdus()
	{
		if (this->retetar.confirmareComanda())
			return true;
		else
			return false;
	}
	void lansareComandaProdus() {
		this->retetar.lansareComanda();
	}

	friend ostream& operator<<(ostream& out, const Produs& p) {
		out << "\n----PRODUS----";
		out << "\nDenumire: " << p.denumire;
		Retetar NUL;
		if (p.retetar != NUL)
			out << p.retetar;
		out << "\nPret produs: " << p.pret;
		out << "\nCantitate produs: " << p.cantitateProdus;
		if (p.valoriNutritionale != nullptr && p.cantitateValoriNutritionale != nullptr) {
			out << "\nValori nutritionale: ";
			out << "\n	Calorii: " << p.cantitateValoriNutritionale[0];
			out << "\n	Proteine:  " << p.cantitateValoriNutritionale[1];
			out << "\n	Carbohidrati: " << p.cantitateValoriNutritionale[2];
		}
		return out;
	}
	friend istream& operator>>(istream& in, Produs& p) {
		cout << "\nIntroduceti denumire produs: ";
		in >> p.denumire;
		if (p.denumire == "")
			p.denumire = "Necunoscuta";

		cout << "\nIntroduceti retetar:";
		in >> p.retetar;

		cout << "\nIntroduceti pret: ";
		in >> p.pret;
		if (p.pret < 0)
			p.pret = 0;

		cout << "\nIntroduceti cantitatea produsului: ";
		in >> p.cantitateProdus;
		if (p.cantitateProdus < 0)
			p.cantitateProdus = 0;

		delete[] p.valoriNutritionale;
		p.valoriNutritionale = new ValoriNutritionale[3];
		p.valoriNutritionale[0] = ValoriNutritionale::CALORII;
		p.valoriNutritionale[1] = ValoriNutritionale::PROTEINE;
		p.valoriNutritionale[2] = ValoriNutritionale::CARBOHIDRATI;

		delete[] p.cantitateValoriNutritionale;
		p.cantitateValoriNutritionale = new float[3];
		cout << "\nIntroduceti caloriile: ";
		in>> p.cantitateValoriNutritionale[0];
		cout << "\nIntroduceti proteinele: ";
		in >> p.cantitateValoriNutritionale[1];
		cout << "\nIntroduceti carbohidratii: ";
		in >> p.cantitateValoriNutritionale[2];
		for (int i = 0; i < 3; i++)
			if (p.cantitateValoriNutritionale[i] < 0)
				p.cantitateValoriNutritionale[i] = 0;
		return in;
	}
	Produs& operator =(const Produs& p) {
		if (this != &p) {
			delete[] this->valoriNutritionale;
			delete[] this->cantitateValoriNutritionale;
			this->cantitateValoriNutritionale = nullptr;
			this->cantitateValoriNutritionale = nullptr;

			if (p.denumire != "")
				this->denumire = p.denumire;
			this->retetar = p.retetar;
			if (p.pret > 0)
				this->pret = p.pret;
			if (p.cantitateProdus > 0)
				this->cantitateProdus = p.cantitateProdus;
			if (p.valoriNutritionale != nullptr && p.cantitateValoriNutritionale != nullptr) {
				this->valoriNutritionale = new ValoriNutritionale[3];
				this->cantitateValoriNutritionale = new float[3];
				for (int i = 0; i < 3; i++) {
					this->valoriNutritionale[i] = p.valoriNutritionale[i];
					if (p.cantitateValoriNutritionale[i] > 0)
						this->cantitateValoriNutritionale[i] = p.cantitateValoriNutritionale[i];
					else
						this->cantitateValoriNutritionale[i] = 0;
				}
			}
		}
		return *this;
	}
	bool operator<(const Produs& p) {
		if (p.pret > 0 && this->pret > 0) {
			if (this->pret < p.pret)
				return true;
			else
				return false;
		}
	}
	bool operator==(const Produs& p) {
		if (p.pret > 0 && this->pret > 0) {
			if (this->pret = p.pret)
				return true;
			else
				return false;
		}
	}

	//pt faza 2
	friend ifstream& operator>>(ifstream& in, Produs& p) {
		in >> p.denumire;
		in >> p.retetar;
		in >> p.pret;
		in >> p.cantitateProdus;
		delete[] p.valoriNutritionale;
		p.valoriNutritionale = new ValoriNutritionale[3];
		p.valoriNutritionale[0] = ValoriNutritionale::CALORII;
		p.valoriNutritionale[1] = ValoriNutritionale::PROTEINE;
		p.valoriNutritionale[2] = ValoriNutritionale::CARBOHIDRATI;
		delete[] p.cantitateValoriNutritionale;
		p.cantitateValoriNutritionale = new float[3];
		for (int i = 0; i < 3; i++)
			in >> p.cantitateValoriNutritionale[i];
		return in;
	}
	void scrieFisierBinProdus(fstream& file) {
		int lungimeDenumire = this->denumire.size() + 1;
		file.write((char*)&lungimeDenumire, sizeof(int));
		file.write(this->denumire.data(), lungimeDenumire);
		this->retetar.scrieFisierBin(file);
		file.write((char*)&this->pret, sizeof(int));
		for (int i = 0; i < 3; i++)
			file.write((char*)&this->valoriNutritionale[i], sizeof(ValoriNutritionale));
		for (int i = 0; i < 3; i++)
			file.write((char*)&this->cantitateValoriNutritionale[i], sizeof(float));
	}
	float getTimpPregatireProdus() {
		return this->retetar.getTimpPregatire();
	}
};

class Meniu {
private:
	int nrProduse=0;
	Produs* produs = nullptr;
public:
	Meniu(){}
	Meniu(Produs* produse, int nrProduse) {
		if (produse != nullptr && nrProduse > 0) {
			this->nrProduse = nrProduse;
			this->produs = new Produs[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
				this->produs[i] = produse[i];
		}
	}
	Meniu(const Meniu& m) {
		if (m.produs != nullptr && m.nrProduse > 0) {
			this->nrProduse = m.nrProduse;
			this->produs = new Produs[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
				this->produs[i] = m.produs[i];
		}
	}
	~Meniu() {
		delete[] this->produs;
		this->produs = nullptr;
	}

	void setMeniu(Produs* produs, int nrProduse) {
		if (produs != nullptr && nrProduse > 0) {
			delete[] this->produs;
			this->nrProduse = nrProduse;
			this->produs = new Produs[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
				this->produs[i] = produs[i];
		}
	}
	int getNrProduseMeniu() {
		return this->nrProduse;
	}
	const Produs* getProduseMeniu() {
		return this->produs;
	}

	void afisare() {
		cout << "\n----------Meniu----------";
		for (int i = 0; i < this->nrProduse; i++) {
			this->produs[i].afisareProdus();
			cout << endl;
		}
	}
	Produs* preluareComanda() {
		int nrProduseComandate;
		cout << "\n		Pentru a comanda introduceti numarul de produse pe care vreti sa le comandati: ";
		cin >> nrProduseComandate;
		if (nrProduseComandate < 0) {
			cout << "\nNumar produse incorect. Incercati din nou.";
			return preluareComanda();
		}
		int counter = 0;
		Produs* produseComandate = new Produs[nrProduseComandate + 1];
		cout << "\n		Introduceti numele produsuelor exact cum este scris in meniu!:";
		for (int i = 0; i < nrProduseComandate; i++) {
			string temp;
			cin >> temp;
			for (int j = 0; j < this->nrProduse; j++) {
				if (temp == this->produs[j].getDenumireProdus()) {
					if (this->produs[j].confirmareComandaProdus()) {
						this->produs[j].lansareComandaProdus();
						produseComandate[i] = this->produs[j];
						counter++;
						break;
					}
					else {
						cout << "\nComanda nu poate fi plasata, lipsa stoc " << temp << ".";
						return nullptr;
					}
				}
			}
		}
		if (counter == nrProduseComandate) {
			cout << "\nComanda plasata";
			return produseComandate;
		}
		else {
			cout << "\nNume produse gresit.Incercati din nou.";
			return preluareComanda();
		}
		delete[] produseComandate;
	}

	Meniu operator=(const Meniu& m) {
		if (this != &m) {
			delete[] this->produs;
			this->produs = nullptr;

			if (m.produs != nullptr && m.nrProduse > 0) {
				this->nrProduse = m.nrProduse;
				this->produs = new Produs[this->nrProduse];
				for (int i = 0; i < this->nrProduse; i++)
					this->produs[i] = m.produs[i];
			}
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Meniu& m) {
		out << "\n----Meniu----";
		out << "\nNr produse: " << m.nrProduse;
		if (m.produs != nullptr && m.nrProduse > 0) {
			for (int i = 0; i < m.nrProduse; i++)
				out << m.produs[i];
		}
		return out;
	}
	friend istream& operator>>(istream& in, Meniu& m) {
		cout << "\nIntroduceti nr produselor din meniu: ";
		in >> m.nrProduse;
		if (m.nrProduse < 0)
			m.nrProduse = 0;
		if (m.nrProduse > 0) {
			cout << "\nIntroduceti produsele: ";
			delete[] m.produs;
			m.produs = new Produs[m.nrProduse];
			for (int i = 0; i < m.nrProduse; i++)
				in >> m.produs[i];
		}
		return in;
	}
	//pt faza 2
	void scrieFisierBinMeniu(fstream& f) {
		f.write((char*)&this->nrProduse, sizeof(int));
		for (int i = 0; i < this->nrProduse; i++)
			this->produs[i].scrieFisierBinProdus(f);
	}
};

class Comanda {
private:
	const int id;
	Produs* produseComandate = nullptr;
	int nrProduseComandate = 0;
	static int generatorId;
public:
	Comanda():id(Comanda::generatorId++){
		this->produseComandate = nullptr;
		this->nrProduseComandate = 0;
	}
	Comanda(Produs* produseComandate, int nrProduseComandate) :id(Comanda::generatorId++) {
		if (produseComandate != nullptr && nrProduseComandate > 0) {
			this->nrProduseComandate = nrProduseComandate;
			this->produseComandate = new Produs[this->nrProduseComandate];
			for (int i = 0; i < this->nrProduseComandate; i++)
				this->produseComandate[i] = produseComandate[i];
		}
	}
	Comanda(const Comanda& c):id(c.id) {
		if (c.produseComandate != nullptr && c.nrProduseComandate > 0) {
			this->nrProduseComandate = c.nrProduseComandate;
			this->produseComandate = new Produs[this->nrProduseComandate];
			for (int i = 0; i < this->nrProduseComandate; i++)
				this->produseComandate[i] = c.produseComandate[i];
		}
	}
	~Comanda() {
		delete[] this->produseComandate;
		this->produseComandate = nullptr;

	}
	
	void setProduseComandate(Produs* produseCoomandate, int nrProduseComandate) {
		if (produseComandate != nullptr && nrProduseComandate > 0) {
			delete[] this->produseComandate;
			this->nrProduseComandate = nrProduseComandate;
			this->produseComandate = new Produs[this->nrProduseComandate];
			for (int i = 0; i < this->nrProduseComandate; i++)
				this->produseComandate[i] = produseComandate[i];
		}
	}
	static void setGeneratorId(int nr) {
		Comanda::generatorId = nr;
	}

	int getNrProduseComandate() {
		return this->nrProduseComandate;
	}
	const Produs* getProduseComandate() {
		return this->produseComandate;
	}
	const int getId() {
		return this->id;
	}
	float getPretComanda() {
		float pret = 0;
		if (this->produseComandate != nullptr && this->nrProduseComandate > 0) {
			for (int i = 0; i < this->nrProduseComandate; i++)
				pret += this->produseComandate[i].getPretProdus();
		}
		return pret;
	}
	float celMaiMareProduus() {
		float max = 0;
		for (int i = 0; i < this->nrProduseComandate; i++)
			if (this->produseComandate[i].getCantitateProdus() > max)
				max = this->produseComandate[i].getCantitateProdus();
		return max;
	}
	float TimpPregatireMediu() {
		float sum = 0;
		for (int i = 0; i < this->nrProduseComandate; i++) {
			sum += produseComandate[i].getTimpPregatireProdus();
		}
		return sum / this->nrProduseComandate;
	}
	void afisareComanda() {
		cout << "\n**Comanda " << this->id;
		cout << "\nNr produse comandate: "<<this->nrProduseComandate;
		cout << "\nProduse Comandate: ";
		for (int i = 0; i < this->nrProduseComandate; i++) {
			cout << this->produseComandate[i].getDenumireProdus() << " ";
		}
		cout << "\nTimp pregatire: ";
		for (int i = 0; i < this->nrProduseComandate; i++) {
			this->produseComandate[i].afisareTimpPregatire();
			cout << " ";
		}
		float total=this->getPretComanda();
		cout << "\nPret total: "<<total<<" lei";
		
	}
	
	Comanda& operator=(const Comanda& c) {
		if (this != &c) {
			delete[] this->produseComandate;
			this->produseComandate = nullptr;

			if (c.produseComandate != nullptr && c.nrProduseComandate > 0) {
				this->nrProduseComandate = c.nrProduseComandate;
				this->produseComandate = new Produs[this->nrProduseComandate];
				for (int i = 0; i < this->nrProduseComandate; i++)
					this->produseComandate[i] = c.produseComandate[i];
			}
		}
		return *this;
	}
	Comanda& operator!(){
		this->nrProduseComandate = 0;
		delete[] this->produseComandate;
		this->produseComandate = nullptr;
		return *this;
	}
	friend ostream& operator <<(ostream& out, const Comanda& c) {
		out << "\n----Comanda nr " << c.id << "----";
		out << "\nNr produse comandate:"<<c.nrProduseComandate;
		if (c.produseComandate != nullptr && c.nrProduseComandate > 0){
			for (int i = 0; i < c.nrProduseComandate; i++)
				out << c.produseComandate[i];
		}
		return out;
	}
	friend istream& operator>>(istream& in, Comanda& c) {
		cout << "\nIntroduceti nr produse comandate: ";
		in >> c.nrProduseComandate;
		if (c.nrProduseComandate < 0)
			c.nrProduseComandate = 0;
		if (c.nrProduseComandate > 0)
			for (int i = 0; i < c.nrProduseComandate; i++)
				in >> c.produseComandate[i];
		return in;
	}
	
	void scrieFisierBinar(fstream& file) {
		file.write((char*)&this->id, sizeof(int));
		file.write((char*)&this->nrProduseComandate, sizeof(int));
		for (int i = 0; i < this->nrProduseComandate; i++)
			this->produseComandate[i].scrieFisierBinProdus(file);
	}
	
};
int Comanda::generatorId = 1;

class Client {
private:
	string nume = "Necunoscut";
	list <Comanda> istoricComenzi;

public:
	Client() {}
	Client(const string& nume, const list< Comanda>& istoricComenzi): nume(nume), istoricComenzi(istoricComenzi) {}
	Client(const Client& c) :nume(c.nume), istoricComenzi(c.istoricComenzi) {}
	Client operator =(const Client& c) {
		if (this != &c) {
			this->nume = c.nume;
			this->istoricComenzi = c.istoricComenzi;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Client& c) {
		out << "---CLIENT---";
		out << "\nNume: " << c.nume;
		if (c.istoricComenzi.size() > 0) {
			out << "\nIstoric Comenzi:";
			for (auto it = c.istoricComenzi.begin(); it != c.istoricComenzi.end(); it++)
				out << *it;
		}
		return out;
	}
	
	void ScrieRapoarteFisier(ofstream&file) {
		file << endl;
		file << "Nume client: " << this->nume<<endl;
		float pretComanda = 0;
		for (auto it = this->istoricComenzi.begin(); it != this->istoricComenzi.end(); it++) {
			 pretComanda += it->getPretComanda();
		}
		file << "Total incasari: " << pretComanda << endl;
		file << "Produsele cu cea mai mare cantitate: ";
		for (auto it = this->istoricComenzi.begin(); it != this->istoricComenzi.end(); it++) {
			file << it->celMaiMareProduus() << " ";
		}
		file << endl;
		file << "Timp de pregatire mediu: ";
		float sum = 0;
		int counter=0;
		for (auto it = this->istoricComenzi.begin(); it != this->istoricComenzi.end(); it++) {
			sum += it->TimpPregatireMediu();
			counter++;
		}
		float avg = sum / counter;
		file << avg << endl;

	}
	void ScrieRapoarteConsola() {
		cout << "\nNume client: " << this->nume << endl;
		float pretComanda = 0;
		for (auto it = this->istoricComenzi.begin(); it != this->istoricComenzi.end(); it++) {
			pretComanda += it->getPretComanda();
		}
		cout << "Total incasari: " << pretComanda << endl;
		cout << "Produsele cu cea mai mare cantitate: ";
		for (auto it = this->istoricComenzi.begin(); it != this->istoricComenzi.end(); it++) {
			cout << it->celMaiMareProduus() << " ";
		}
		cout << endl;
		cout << "Timp de pregatire mediu: ";
		float sum = 0;
		int counter = 0;
		for (auto it = this->istoricComenzi.begin(); it != this->istoricComenzi.end(); it++) {
			sum += it->TimpPregatireMediu();
			counter++;
		}
		float avg = sum / counter;
		cout << avg << endl;
	}
};

set<MateriePrima> initializareStocDinFisierTxt1(const char* numeFisier) {
	set<MateriePrima> stocFisier;
	ifstream fisier(numeFisier);

	if (fisier.is_open()) {
		MateriePrima materiePrima;

		while (fisier >> materiePrima) {
			stocFisier.insert(materiePrima);
		}

		fisier.close();
	}
	else {
		cout << "Eroare la deschiderea fisierului " << numeFisier << endl;
	}

	return stocFisier;
}
vector <Produs> citesteVectorProduseDinFisier(const char* numeFisier) {
	vector<Produs> vectorProduse;
	ifstream fisier(numeFisier);

	if (fisier.is_open()) {
		Produs produs;

		while (fisier >> produs) {
			vectorProduse.push_back(produs);
		}

		fisier.close();
	}
	else {
		cout << "Eroare la deschiderea fisierului " << numeFisier << endl;
	}

	return vectorProduse;
}
int main(int nrArgumente, char* Argumente[]) {
	
	set<MateriePrima>stocDinFisier =initializareStocDinFisierTxt1("TextFile1.txt");
	int dimStoc = stocDinFisier.size();
	MateriePrima* stoc = new MateriePrima[dimStoc];
	int i = 0;
	for (auto it = stocDinFisier.begin(); it != stocDinFisier.end(); it++) {
		stoc[i] = *it;
		i++;
	}
	Retetar::setStoc(stoc, dimStoc);
	//Retetar::afisareStoc();

	fstream fileStoc("Stoc.bin", ios::out | ios::binary);
	for (int i = 0; i < dimStoc; i++)
		stoc[i].scrieFisierBin(fileStoc);
	fileStoc.close();

	vector<Produs>produseDinFisier = citesteVectorProduseDinFisier("TextFile2.txt");
	int dimMeniu = produseDinFisier.size();
	Produs* produseMeniu = new Produs[dimMeniu];
	produseMeniu = produseDinFisier.data();
	Meniu m(produseMeniu, dimMeniu);
	m.afisare();

	fstream fileMeniu("Meniu.bin", ios::out | ios::binary);
	m.scrieFisierBinMeniu(fileMeniu);
	fileMeniu.close();
	
	string nume;
	Comanda comenzi[100];
	int continua = 1;
	int indexComanda = 0;
	cout << "\nIntroduceti numele dvs:\n ";
	cin >> nume;
	while (continua == 1) {
		Produs* produseComandate = m.preluareComanda();
		int nrProduseComandate = 0;
		while (produseComandate[nrProduseComandate].getDenumireProdus() != "Necunoscuta") {
			nrProduseComandate++;
		}
		comenzi[indexComanda] = Comanda(produseComandate, nrProduseComandate);
		cout << "\n	 Pentru plasarea altei comenzi apasati 1, altfel 0: ";
		cin >> continua;
		if (continua == 1)
			indexComanda++;
	}
	
	for (int i = 0; i <= indexComanda; i++) 
		comenzi[i].afisareComanda();
	list< Comanda> comandaClient;
	for (int i = 0; i <=indexComanda; i++) {
		comandaClient.push_back(comenzi[i]);
	}
	Client cl(nume, comandaClient);
	ofstream fileClient("Rapoarte.txt", ios::app);
	cout << "\nRaport: ";
	cl.ScrieRapoarteConsola();
	cl.ScrieRapoarteFisier(fileClient);
	fileClient.close();
	/*apel verificare citire si scriere fisiere bin*/
	/*
	MateriePrima m1, m2;
	fstream file("MateriiPrime.bin", ios::in | ios::binary);
	m1.citesteFisierBin(file);
	m2.citesteFisierBin(file);
	file.close(); 
	MateriePrima m[] = {m1, m2};
	float cantitati[] = { 3.3, 4.4 };
	MateriePrima mm[] = { m2,m1 };
	float cantitati2[] = { 1.1, 2.2 };
	Retetar r1(2, m, cantitati, 10);
	Retetar r2(2, mm, cantitati2, 20);
	fstream fileRetetar("Retetar.bin", ios::in | ios::binary);
	r1.citesteFisierBin(fileRetetar);
	r2.citesteFisierBin(fileRetetar);
	cout << r1 << r2;
	cout << m1 << m2;

	file.close();
	fileRetetar.close();
	*/
	return 0;
}