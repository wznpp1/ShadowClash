#ifndef APPVERSIONUTIL_H
#define APPVERSIONUTIL_H


class AppVersionUtil
{
public:
    static void init();
    static bool isFirstLaunch();
    static bool hasVersionChanged();
};

#endif // APPVERSIONUTIL_H
