class Character
{
public:
    Character()
    {
    }

    void moveNorth()
    {
        latitude += 0.01;
    }

    void moveSouth()
    {
        latitude -= 0.01;
    }

    void moveEast()
    {
        longitude += 0.01;
    }

    void moveWest()
    {
        longitude -= 0.01;
    }

    float getLongitude() {
        return longitude;
    }

    float getLatitude() {
        return latitude;
    }


private:
    float longitude = 0.0f;
    float latitude = 0.0f;
};