#ifndef THEME_MANAGER_H
#define THEME_MANAGER_H

template<typename T>
class Singleton;
class QString;

class ThemeManager{
public:
    ~ThemeManager();
public:
    static ThemeManager *instance();
public:
    QString styleSheet(const QString &path) const;
private:
    friend class Singleton<ThemeManager>;
private:
    ThemeManager();
private:
    ThemeManager(const ThemeManager&);
    ThemeManager &operator=(const ThemeManager&);
};

#endif // THEME_MANAGER_H
