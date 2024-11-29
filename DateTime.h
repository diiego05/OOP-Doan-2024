#ifndef DATETIME_H
#define DATETIME_H

#include <string>
#include <iostream>
#include <ctime>
using namespace std;

class DateTime {
public:
    int day, month, year, hour, minute;

    // Constructor mặc định
    DateTime() : day(0), month(0), year(0), hour(0), minute(0) {}

    // Constructor với các tham số
    DateTime(int d, int m, int y, int h, int min)
        : day(d), month(m), year(y), hour(h), minute(min) {}

    // Hiển thị ngày giờ dưới dạng chuỗi
    void displayDateTime() const {
        cout << day << "/" << month << "/" << year << " " << hour << ":" << minute << endl;
    }

    // Chuyển đổi đối tượng DateTime thành chuỗi
    string toString() const {
        return to_string(day) + "/" + to_string(month) + "/" +
               to_string(year) + " " + to_string(hour) + ":" +
               to_string(minute);
    }

    // Kiểm tra tính hợp lệ của ngày giờ
    bool isValid() const {
        if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31 || hour < 0 || hour >= 24 || minute < 0 || minute >= 60)
            return false;
        
        // Kiểm tra các tháng có 30 ngày
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
            return false;

        // Kiểm tra tháng 2 (Ngày 29 cho năm nhuận)
        if (month == 2) {
            bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if ((isLeap && day > 29) || (!isLeap && day > 28))
                return false;
        }
        return true;
    }

    // Kiểm tra xem thời gian hiện tại có muộn hơn đối tượng DateTime này hay không
    bool isLaterThan(const DateTime& other) const {
        if (year > other.year) return true;
        if (year == other.year && month > other.month) return true;
        if (year == other.year && month == other.month && day > other.day) return true;
        if (year == other.year && month == other.month && day == other.day && hour > other.hour) return true;
        if (year == other.year && month == other.month && day == other.day && hour == other.hour && minute > other.minute)
            return true;
        return false;
    }

    // Lấy ngày giờ hiện tại
    DateTime getCurrentDate() {
        time_t now = time(0);
        tm *ltm = localtime(&now);

        // Khởi tạo đối tượng DateTime với ngày giờ hiện tại
        return DateTime(
            ltm->tm_mday,
            1 + ltm->tm_mon,
            1900 + ltm->tm_year,
            ltm->tm_hour,
            ltm->tm_min
        );
    }

    // Tính số ngày giữa 2 ngày
    int calculateDaysDifference(const DateTime &end, const DateTime &current) {
        auto toDays = [](const DateTime &dt) {
            return dt.year * 365 + dt.month * 30 + dt.day;
        };

        return toDays(current) - toDays(end);
    }
};

#endif
