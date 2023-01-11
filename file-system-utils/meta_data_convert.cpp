#include <string>
#include <cmath>
#include "meta_data_convert.hpp"
#include "../file-system-domain/enums/file_type.cpp"

namespace MetaDataConvert
{
    std::string convertFileTypeToString(FileType fileType)
    {
        switch (fileType)
        {
        case FileType::Symlink:
            return "Symbolic Link";
        case FileType::Directory:
            return "Directory";
        case FileType::File:
            return "Ordinary File";
        }
    }

    // NOTE: The following code snippet is not authored by me
    //    
    /* Author: AshutoshShisodia, https://auth.geeksforgeeks.org/user/AshutoshShisodia
     * Date of last update: 06 Oct, 2022
     * Title of code snippet: Convert Unix timestamp to DD/MM/YYYY HH:MM:SS format
     * Type: code snippet
     * Web address or article: https://www.geeksforgeeks.org/convert-unix-timestamp-to-dd-mm-yyyy-hhmmss-format/
     * 
     */
    std::string convertUnixTimeStampToString(long timestamp)
    {
        // Save the time in Human
        // readable format
        std::string result = "";

        // Number of days in month
        // in normal year
        int daysOfMonth[] = {31, 28, 31, 30, 31, 30,
                             31, 31, 30, 31, 30, 31};

        long int currYear, daysTillNow, extraTime, extraDays,
            index, date, month, hours, minutes, secondss,
            flag = 0;

        // Calculate total days unix time T
        daysTillNow = timestamp / (24 * 60 * 60);
        extraTime = timestamp % (24 * 60 * 60);
        currYear = 1970;

        // Calculating current year
        while (true)
        {
            if (currYear % 400 == 0 || (currYear % 4 == 0 && currYear % 100 != 0))
            {
                if (daysTillNow < 366)
                {
                    break;
                }
                daysTillNow -= 366;
            }
            else
            {
                if (daysTillNow < 365)
                {
                    break;
                }
                daysTillNow -= 365;
            }
            currYear += 1;
        }
        // Updating extradays because it
        // will give days till previous day
        // and we have include current day
        extraDays = daysTillNow + 1;

        if (currYear % 400 == 0 || (currYear % 4 == 0 && currYear % 100 != 0))
            flag = 1;

        // Calculating MONTH and DATE
        month = 0, index = 0;
        if (flag == 1)
        {
            while (true)
            {

                if (index == 1)
                {
                    if (extraDays - 29 < 0)
                        break;
                    month += 1;
                    extraDays -= 29;
                }
                else
                {
                    if (extraDays - daysOfMonth[index] < 0)
                    {
                        break;
                    }
                    month += 1;
                    extraDays -= daysOfMonth[index];
                }
                index += 1;
            }
        }
        else
        {
            while (true)
            {

                if (extraDays - daysOfMonth[index] < 0)
                {
                    break;
                }
                month += 1;
                extraDays -= daysOfMonth[index];
                index += 1;
            }
        }

        // Current Month
        if (extraDays > 0)
        {
            month += 1;
            date = extraDays;
        }
        else
        {
            if (month == 2 && flag == 1)
                date = 29;
            else
            {
                date = daysOfMonth[month - 1];
            }
        }

        // Calculating HH:MM:YYYY
        hours = extraTime / 3600;
        minutes = (extraTime % 3600) / 60;
        secondss = (extraTime % 3600) % 60;

        result += std::to_string(date);
        result += "/";
        result += std::to_string(month);
        result += "/";
        result += std::to_string(currYear);
        result += " ";
        result += std::to_string(hours);
        result += ":";
        result += std::to_string(minutes);
        result += ":";
        result += std::to_string(secondss);

        // Return the time
        return result;
    }
}