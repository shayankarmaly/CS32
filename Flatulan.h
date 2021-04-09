#ifndef FLATULAN_H
#define FLATULAN_H


class City;

class Flatulan
{
  public:
        // Constructor
    Flatulan(City* cp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;
    bool haveIBeenConverted() const;

        // Mutators
    void move();

  private:
    City* m_city;
    int   m_row;
    int   m_col;
};


#endif /* Flatulan_h */
