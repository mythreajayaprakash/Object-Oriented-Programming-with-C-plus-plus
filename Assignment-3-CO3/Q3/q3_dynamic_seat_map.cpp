#include <iostream>
#include <stdexcept>

class Event {
    int rows;
    int seatsPerRow;
    bool** seats;

public:
    Event(int r, int s) : rows(r), seatsPerRow(s), seats(nullptr) {
        if (r < 0 || s < 0) throw std::invalid_argument("dimensions cannot be negative");
        if (rows > 0 && seatsPerRow > 0) {
            seats = new bool*[rows]{};
            try {
                for (int i = 0; i < rows; ++i) seats[i] = new bool[seatsPerRow]{false};
            } catch (...) {
                for (int i = 0; i < rows; ++i) delete[] seats[i];
                delete[] seats;
                throw;
            }
        }
        std::cout << "Event opened: " << rows << " x " << seatsPerRow << '\n';
    }

    bool book(int r, int s) {
        if (!valid(r, s) || seats[r][s]) return false;
        seats[r][s] = true;
        return true;
    }

    bool cancel(int r, int s) {
        if (!valid(r, s) || !seats[r][s]) return false;
        seats[r][s] = false;
        return true;
    }

    ~Event() {
        if (seats) {
            for (int i = 0; i < rows; ++i) delete[] seats[i];
            delete[] seats;
        }
        std::cout << "Event closed; released " << rows * seatsPerRow << " seats\n";
    }

private:
    bool valid(int r, int s) const {
        return r >= 0 && r < rows && s >= 0 && s < seatsPerRow && seats != nullptr;
    }
};

int main() {
    Event local(2, 3);
    local.book(0, 1);
    local.cancel(0, 1);

    {
        Event block(1, 2);
        block.book(0, 0);
    }

    Event* dynamic = new Event(2, 2);
    dynamic->book(1, 1);
    delete dynamic;

    Event zero(0, 5);
    (void)zero;
    return 0;
}
