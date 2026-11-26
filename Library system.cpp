#include <iostream> 
#include <string>   
#include <vector>   
using namespace std;  

class LibrarySystem { // كلاس نظام إدارة المكتبة
private:
    // قائمة الكتب المتاحة حالياً في المكتبة
    vector<string> library = { "7 Habits of Highly Effective People", "The Power of Now", "atomic habits" };
    // قائمة الكتب اللي المستخدم استعارها حالياً
    vector<string> borrowedBooks;//فكتور علشان يعمل زي اريي ل الاسترينج

public:
    // دالة لعرض القائمة الرئيسية للخيارات المتاحة للمستخدم
    void displayMenu() {
        cout << "\n========= Library System =========\n";
        cout << "1. View Available Books\n";
        cout << "2. Borrow a Book\n";
        cout << "3. Return a Book\n";
        cout << "4. View My Borrowed Books\n";
        cout << "5. Add a Book to Library\n";
        cout << "6. Exit\n";
        cout << "Choose an option: ";
    }

    // دالة لعرض كل الكتب المتاحة في المكتبة
    void viewAvailableBooks() {
        cout << "\nAvailable Books:\n";
        // التحقق هل قائمة الكتب المتاحة فاضية ولا لأ
        if (library.empty()) {
            cout << "No books available.\n";
            return; // الخروج من الدالة مبكراً لعدم وجود كتب
        }
        // المرور على الكتب المتاحة وطباعتها مرقمة بدءاً من 1
        for (int i = 0; i < (int)library.size(); i++) {
            cout << i + 1 << ". " << library[i] << endl;
        }
    }

    // دالة لعرض الكتب المستعارة حالياً
    void viewBorrowedBooks() {
        cout << "\nBorrowed Books:\n";
        // التحقق هل يوجد كتب مستعارة ولا لأ
        if (borrowedBooks.empty()) {
            cout << "No borrowed books.\n";
            return;
        }
        // طباعة قائمة الكتب المستعارة مرقمة
        for (int i = 0; i < (int)borrowedBooks.size(); i++) {
            cout << i + 1 << ". " << borrowedBooks[i] << endl;
        }
    }

    // دالة لاستعارة كتاب من المكتبة
    void borrowBook() {
        viewAvailableBooks(); // عرض الكتب المتاحة أولاً ليختار منها المستخدم
        if (library.empty()) return; // لو مفيش كتب متاحة ننهي العملية

        int num; // متغير لتخزين رقم الكتاب المختار
        cout << "Enter the number of the book to borrow: ";
        cin >> num;

        // التحقق من أن الرقم المدخل ضمن النطاق الصحيح للقائمة
        if (num < 1 || num >(int)library.size()) {
            cout << "Invalid choice.\n";
            return;
        }

        cout << "You borrowed: " << library[num - 1] << endl;
        // إضافة الكتاب إلى قائمة الكتب المستعارة
        borrowedBooks.push_back(library[num - 1]);
        // حذف الكتاب من قائمة الكتب المتاحة لأنه أصبح مستعاراً
        library.erase(library.begin() + (num - 1));
    }

    // دالة لإرجاع كتاب مستعار إلى المكتبة
    void returnBook() {
        viewBorrowedBooks(); // عرض الكتب المستعارة حالياً
        if (borrowedBooks.empty()) return; // لو مفيش كتب مستعارة ننهي العملية

        int num; // متغير لتخزين رقم الكتاب المراد إرجاعه
        cout << "Enter the number of the book to return: ";
        cin >> num;

        // التأكد من صحة رقم الاختيار المدخل
        if (num < 1 || num >(int)borrowedBooks.size()) {
            cout << "Invalid choice.\n";
            return;
        }

        cout << "You returned: " << borrowedBooks[num - 1] << endl;
        // إعادة الكتاب إلى قائمة الكتب المتاحة
        library.push_back(borrowedBooks[num - 1]);
        // إزالة الكتاب من قائمة الكتب المستعارة
        borrowedBooks.erase(borrowedBooks.begin() + (num - 1));
    }

    // دالة لإضافة كتاب جديد إلى المكتبة
    void addBook() {
        string bookName; // متغير لتخزين اسم الكتاب الجديد
        cout << "Enter the name of the book to add: ";
        cin.ignore(); // تجاهل بقايا السطر الجديد (newline) من إدخال سابق
        getline(cin, bookName); // قراءة اسم الكتاب كاملاً حتى لو فيه مسافات
        library.push_back(bookName); // إضافة الكتاب الجديد لنهاية قائمة المكتبة
        cout << bookName << " added to the library.\n";
    }

    // دالة تشغيل البرنامج الرئيسية وإدارة التنقل بين القوائم
    void start() {
        int option; // متغير لتخزين اختيار المستخدم من القائمة
        while (true) { // حلقة مستمرة حتى يختار المستخدم الخروج (رقم 6)
            displayMenu();
            // التحقق أن الإدخال رقم صحيح وليس نصاً أو رمزاً
            if (!(cin >> option)) {
                cout << "Invalid option. Try again.\n";
                cin.clear(); // إعادة ضبط حالة الإدخال بعد الخطأ
                cin.ignore(10000, '\n'); // تجاهل المدخلات الخاطئة حتى نهاية السطر
                continue; // الرجوع لبداية الحلقة لعرض القائمة من جديد
            }

            // تنفيذ العملية المناسبة حسب اختيار المستخدم
            switch (option) {
            case 1:
                viewAvailableBooks();
                break;
            case 2:
                borrowBook();
                break;
            case 3:
                returnBook();
                break;
            case 4:
                viewBorrowedBooks();
                break;
            case 5:
                addBook();
                break;
            case 6:
                cout << "Thanks for using the Library System. Goodbye\n";
                return; // إنهاء الدالة والخروج من البرنامج
            default:
                cout << "Invalid option. Try again.\n"; // في حال إدخال رقم خارج 1 إلى 6
            }
        }
    }
};

int main() {
    LibrarySystem librarySystem; // إنشاء كائن (object) من الكلاس
    librarySystem.start(); // بدء تشغيل النظام
    return 0; // إنهاء البرنامج بنجاح
}
