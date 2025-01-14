#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

// The base Subscriber class is created, forming the foundation for classes derived from different subscriber types.
class Abone 
{
protected:						 																		// Data is defined with protected access type.
    int ID;                      																		// Unique ID number for each subscriber.
    char Ad[50];                 																		// Name of the subscriber.
    char Soyad[50];              																		// Surname of the subscriber.
    int tuketim_miktari;         																		// Consumption amount of the subscriber (e.g., electricity, water, etc.).

public:
    // Constructor function to initialize and define subscriber information.
    Abone(int id, const char* ad, const char* soyad, int tuketim) : ID(id), tuketim_miktari(tuketim) 
	{
        strncpy(Ad, ad, 49);
        Ad[49] = '\0'; 																					// Ensures the last character is a null terminator.
        strncpy(Soyad, soyad, 49);
        Soyad[49] = '\0';
    }

    virtual ~Abone() {} 																				// Virtual destructor ensures proper destruction of derived class objects

    // Pure virtual functions to be implemented by derived classes
    virtual float faturaHesapla() const = 0; 															// Bill calculation is handled by the faturaHesapla() function.
    virtual void yazdir() const = 0;        															// Printing subscriber information is handled by the yazdir() function.
    virtual const char* aboneTipi() const = 0; 															// Function to return the subscriber type is defined by aboneTipi().
};

// Class representing Mesken subscribers.
class Mesken : public Abone 
{
private:
    static const int tuketim_limiti = 150;           													// Consumption limit is defined.
    static const float birim_fiyat;                 													// Unit price within the limit is defined.
    static const float limit_ustu_birim_fiyat;      													// Unit price for consumption above the limit is defined.

public:
    // Constructor function for the Mesken class.
    Mesken(int id, const char* ad, const char* soyad, int tuketim) : Abone(id, ad, soyad, tuketim) {}

    // Calculates the bill amount based on consumption using the faturaHesapla function.
    float faturaHesapla() const override 
	{
        if (tuketim_miktari <= tuketim_limiti)
            return tuketim_miktari * birim_fiyat;
        else
            return tuketim_limiti * birim_fiyat + (tuketim_miktari - tuketim_limiti) * limit_ustu_birim_fiyat;
    }

   // Formats and prints subscriber information using the yazdir() function.
    void yazdir() const override 
	{
        cout << left << setw(5) << ID << setw(15) << Ad << setw(15) << Soyad << setw(15) << tuketim_miktari << fixed << setprecision(2) << faturaHesapla() << endl;
    }

    // Returns the subscriber type: "M" for residential subscribers.
    const char* aboneTipi() const override 
	{
        return "M";
    }
};

// Static member variables for the Mesken class are defined.
const float Mesken::limit_ustu_birim_fiyat = 2.4;
const float Mesken::birim_fiyat = 1.4;

// Class representing corporate subscribers.
class Kurumsal : public Abone 
{
protected:
    char kurum_adi[100]; 																				/// Name of the organization the subscriber is associated with.

public:
    // Constructor function for the Kurumsal class.
    Kurumsal(int id, const char* ad, const char* soyad, int tuketim, const char* kurumAdi) : Abone(id, ad, soyad, tuketim) 
	{
        strncpy(kurum_adi, kurumAdi, 99);
        kurum_adi[99] = '\0'; 																			// Ensures the last character is a null terminator.
    }

    // Prints subscriber information using the yazdir() function.
    void yazdir() const override 
	{
        cout << left << setw(5) << ID << setw(15) << Ad << setw(15) << Soyad << setw(20) << kurum_adi << setw(15) << tuketim_miktari << fixed << setprecision(2) << faturaHesapla() << endl;
    }
};

// Derived class for Corporate Industrial subscribers.
class KurumsalSanayi : public Kurumsal 
{
private:
    static const float birim_fiyat; 																	// Fixed unit price for industrial subscribers.

public:
    // Constructor function for the KurumsalSanayi class.
    KurumsalSanayi(int id, const char* ad, const char* soyad, int tuketim, const char* kurumAdi) : Kurumsal(id, ad, soyad, tuketim, kurumAdi) {}

    // Calculates the bill amount using the specific unit price for industrial subscribers.
    float faturaHesapla() const override 
	{
        return tuketim_miktari * birim_fiyat;
    }

    // Subscriber type: "KS" for Corporate Industrial subscribers.
    const char* aboneTipi() const override 
	{
        return "KS";
    }
};

// Static unit price definition for Corporate Industrial subscribers.
const float KurumsalSanayi::birim_fiyat = 0.4;

// Derived class for Corporate Commercial subscribers.
class KurumsalTicarethane : public Kurumsal 
{
private:
    static const float birim_fiyat; 																		// Fixed unit price for commercial subscribers.

public:
    // Constructor function for the KurumsalTicarethane class.
    KurumsalTicarethane(int id, const char* ad, const char* soyad, int tuketim, const char* kurumAdi) : Kurumsal(id, ad, soyad, tuketim, kurumAdi) {}

    // Calculates the bill amount using the specific unit price for commercial subscribers.
    float faturaHesapla() const override 
	{
        return tuketim_miktari * birim_fiyat;
    }

    // Subscriber type: "KT" for Corporate Commercial subscribers
    const char* aboneTipi() const override 
	{
        return "KT";
    }
};

// Static unit price definition for Corporate Commercial subscribers.
const float KurumsalTicarethane::birim_fiyat = 1.1;

int main() 
{
    // Opens a file containing subscriber information using file operations.
    ifstream file("aboneler.txt");
    if (!file.is_open()) 
	{
        cerr << "!!! File could not be opened, please try again !!!" << endl;
        return 1;
    }

    // Defines an array to store subscriber objects and a variable to track the number of subscribers.
    Abone* aboneler[100];
    int aboneSayisi = 0;

    // Defines variables for the information read from the file.
    char type[3], ad[50], soyad[50], kurumAdi[100];
    int id, tuketim;

    // Reads subscriber information from the file and creates appropriate objects.
    while (file >> type >> id >> ad >> soyad >> tuketim) 
	{
        if (strcmp(type, "M") == 0) 
		{
            aboneler[aboneSayisi++] = new Mesken(id, ad, soyad, tuketim);
        } else if (strcmp(type, "S") == 0 || strcmp(type, "T") == 0) 
		{
            file.get(); 																						// Skips the space character.
            file.getline(kurumAdi, 100);
            if (strcmp(type, "S") == 0) 
			{
                aboneler[aboneSayisi++] = new KurumsalSanayi(id, ad, soyad, tuketim, kurumAdi);
            } else if (strcmp(type, "T") == 0) 
			{
                aboneler[aboneSayisi++] = new KurumsalTicarethane(id, ad, soyad, tuketim, kurumAdi);
            }
        }
    }
    file.close(); 																								// Closes the file.

    // Prints the list of Residential subscribers.
    cout << "Mesken Abone Listesi:" << endl;
    cout << left << setw(5) << "ID" << setw(15) << "Ad" << setw(15) << "Soyad" << setw(15) << "Tuketim" << "Fatura Tutari" << endl;
    cout << string(55, '-') << endl;
    for (int i = 0; i < aboneSayisi; ++i) 
	{
        if (strcmp(aboneler[i]->aboneTipi(), "M") == 0) 
		{
            aboneler[i]->yazdir();
        }
    }

	// Prints the list of Corporate Commercial subscribers.
    cout << "\nKurumsal Ticarethane Abone Listesi:" << endl;
    cout << left << setw(5) << "ID" << setw(15) << "Ad" << setw(15) << "Soyad" << setw(20) << "Kurum Adi" << setw(15) << "Tuketim" << "Fatura Tutari" << endl;
    cout << string(80, '-') << endl;
    for (int i = 0; i < aboneSayisi; ++i) 
	{
        if (strcmp(aboneler[i]->aboneTipi(), "KT") == 0) 
		{
            aboneler[i]->yazdir();
        }
    }

    // Prints the list of Corporate Industrial subscribers.
    cout << "\nKurumsal Sanayi Abone Listesi:" << endl;
    cout << left << setw(5) << "ID" << setw(15) << "Ad" << setw(15) << "Soyad" << setw(20) << "Kurum Adi" << setw(15) << "Tuketim" << "Fatura Tutari" << endl;
    cout << string(80, '-') << endl;
    for (int i = 0; i < aboneSayisi; ++i) 
	{
        if (strcmp(aboneler[i]->aboneTipi(), "KS") == 0) 
		{
            aboneler[i]->yazdir();
        }
    }

    // Deletes dynamically created objects.
    for (int i = 0; i < aboneSayisi; ++i) 
	{
        delete aboneler[i];
    }

    return 0;
}

