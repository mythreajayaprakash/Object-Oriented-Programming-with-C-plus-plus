#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Time {
    int seconds;
public:
    explicit Time(int total = 0) : seconds(total) {
        if (total < 0) throw std::invalid_argument("time cannot be negative");
    }
    Time& operator++() { ++seconds; return *this; }
    Time operator++(int) { Time old(*this); ++seconds; return old; }
    bool operator==(const Time& other) const { return seconds == other.seconds; }
    bool operator<(const Time& other) const { return seconds < other.seconds; }
    int value() const { return seconds; }
    void print() const {
        int h = seconds / 3600, m = (seconds / 60) % 60, s = seconds % 60;
        std::cout << h << ':' << (m < 10 ? "0" : "") << m << ':'
                  << (s < 10 ? "0" : "") << s;
    }
};

class Playlist {
    std::vector<std::string> tracks;
public:
    explicit Playlist(std::vector<std::string> values) : tracks(std::move(values)) {}
    std::string& operator[](int index) {
        if (index < 0 || static_cast<std::size_t>(index) >= tracks.size())
            throw std::out_of_range("playlist index");
        return tracks[static_cast<std::size_t>(index)];
    }
    const std::string& operator[](int index) const {
        if (index < 0 || static_cast<std::size_t>(index) >= tracks.size())
            throw std::out_of_range("playlist index");
        return tracks[static_cast<std::size_t>(index)];
    }
    std::size_t size() const { return tracks.size(); }
};

int main() {
    Time t(3599);
    Time a = t++;
    Time b = ++t;
    a.print(); std::cout << ' '; b.print(); std::cout << ' '; t.print(); std::cout << '\n';

    Playlist playlist({"Song A", "Song B", "Song C"});
    std::cout << "Now playing: " << playlist[0] << '\n';
    playlist[1] = "Updated Song B";
    const Playlist& readOnly = playlist;
    std::cout << "Second track: " << readOnly[1] << '\n';

    for (int index : {-1, 3}) {
        try { std::cout << playlist[index] << '\n'; }
        catch (const std::out_of_range& e) { std::cout << "Range error: " << e.what() << '\n'; }
    }

    Time x(3599);
    ++x; x.print(); std::cout << " (hour rollover)\n";
    return 0;
}
