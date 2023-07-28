// 1. terms ��ȿ�Ⱓ�� ���̴�. �̸� pribacy ���� ���ϰ� 12 �ʰ�(13)�̸� ���� 1 ���Ѵ�. ���� -1 �Ѵ�.
// 2. ��� ���� 28�� �� ���������̴�.
// 3. ������ ��ȿ�Ⱓ ������ ���̸� �����Ѵ�.
// �����ϴ� ����� �������ʴ´�.
// �ް� ���� ���ڸ��θ� ��Ÿ����. ���ڸ��� ��� 05.02 ��.
// �ı��� privacy�� �ݵ�� 1�� �̻��̴�.

#include <string>
#include <vector>
#include <iostream>

#define MAX_DAY 28
#define MAX_PRIVACY 100

using namespace std;

int terms[200];
int privacies_sz;
vector<int> expired; // answer

struct Date {
    int year, month, day;

    bool operator>= (Date date) const {
        if (this->year > date.year) {
            return true;
        }
        if (this->year == date.year) {
            if (this->month > date.month) return true;
            if (this->month == date.month) {
                if (this->day >= date.day) return true;
            }
        }

        return false;
    }
} today;

struct Privacy {
    Date date;
    char term;

} privacies[MAX_PRIVACY];

Date splitDate(string day) {
    day.push_back('.');
    int s = 0, e = 0;
    vector<int> v;

    while (1) {
        e = day.find('.', s);
        if (e == -1) break;
        int sz = e - s;
        string tmp = day.substr(s, sz);
        v.push_back(stoi(tmp));
        s = e + 1;
    }
    return { v[0], v[1], v[2] };
}

void splitTerms(vector<string> termvec) {
    int sz = termvec.size();
    int sep;
    for (string tar : termvec) {
        sep = tar.find(' ', 0);

        string term = tar.substr(0, 1);
        string month = tar.substr(sep + 1);
        // cout << month << endl;
        terms[term[0]] = stoi(month);
    }
}

void parsePrivacies(vector<string> pri) {
    int sz = pri.size();
    for (int i = 0; i < sz; i++) {
        string tar = pri[i];
        int sep = tar.find(' ', 0);

        int date_sz = sep;
        string date = tar.substr(0, date_sz);
        // cout << '.' << date << '.' << endl;

        char term = tar.substr(sep + 1, 1)[0];
        // cout << term << endl;
        privacies[i] = { splitDate(date), term };
    }
}

// �����ϴ� ����� �������ʴ´�.
// �ް� ���� ���ڸ��θ� ��Ÿ����. ���ڸ��� ��� 05.02 ��.
// �ı��� privacy�� �ݵ�� 1�� �̻��̴�.

void getExpired() {
    for (int i = 0; i < privacies_sz; i++) {
        Date agreed = privacies[i].date;
        char term = privacies[i].term;

        // 1. terms ��ȿ�Ⱓ�� ���̴�. �̸� pribacy ���� ���ϰ� ���� -1 �Ѵ�.
        // ���⼭ ���� -1 ���ϰ� ������ ��ȿ�Ⱓ ���� �̻�(��ȿ�Ⱓ�� ���� ����)�̸� expire
        Date expire = { agreed.year, agreed.month + terms[term], agreed.day };


        // 12 �ʰ�(13)�̸� ���� 1 ���Ѵ�. ��ȿ�Ⱓ�� 100�� ���� ������.
        if (expire.month > 12) {
            expire.year += expire.month / 12;
            expire.month = expire.month % 12;
        }
        // 3. ������ ��ȿ�Ⱓ ������ ���̸� �����Ѵ�. = ������ ��ȿ�Ⱓ ���� ũ�� expire
        // ���, day�� �����߱� ������ ������ ��ȿ�Ⱓ ���� �̻�(��ȿ�Ⱓ�� ���� ����)�̸� expire
        if (today >= expire) {
            expired.push_back(i + 1);
        }
    }
}

vector<int> solution(string today_, vector<string> terms_, vector<string> privacies_) {
    // init
    privacies_sz = privacies_.size();
    today = splitDate(today_);
    splitTerms(terms_);
    parsePrivacies(privacies_);

    getExpired();

    return expired;
}