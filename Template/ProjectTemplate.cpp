#include <vector>

#include <tc/tc_startup.h>

#include <tc/emh.h>
#include <tc/tc_util.h>
#include <tcinit/tcinit.h>

#include <base_utils/IFail.hxx>
#include <base_utils/TcResultStatus.hxx>

using namespace std;

namespace $safeprojectname$
{
    inline void itk_check(const int result);

    void print_emh_error(IFail e);
}

extern int ITK_user_main(int argc, char** argv)
{
    int ifail = ITK_ok;
    do
    {
        try
        {

            $safeprojectname$::itk_check(ITK_auto_login());
        }
        catch (IFail& e)
        {
            ifail = e.ifail();
            $safeprojectname$::print_emh_error(e);
        }
    } while (false);

    POM_logout(TRUE);
    ITK_exit_module(TRUE);

    return ifail;
}

void $safeprojectname$::itk_check(const int result)
{
    ResultStatus result_status(result);
}

void $safeprojectname$::print_emh_error(IFail e)
{
    vector<int>    error_codes = {};
    vector<int>    severities = {};
    vector<string> error_messages = {};

    e.getAndClearErrorStack(error_codes, severities, error_messages);
    for (int i = 0; i < static_cast<int>(error_codes.size()); i++)
    {
        const char* severity;

        switch (severities[i])
        {
        case EMH_severity_information:
            severity = "INFO";
            break;
        case EMH_severity_warning:
            severity = "WARNING";
            break;
        case EMH_severity_error:
            severity = "ERROR";
            break;
        case EMH_severity_user_error:
            severity = "USER ERROR";
            break;
        default:
            severity = "UNKNOWN";
            break;
        }

        TC_printf("%-11s %6s: - %s\n", severity, error_codes[i], error_messages[i].c_str());
    }
}