#pragma once
#include <nFramework/nIntegrator/nIntegrator.h>
#include <nFramework/util/util.h>
#include <nFramework/util/IniHandler.h>
#include <nFramework/Log4nf/Loggable.h>
#include <filesystem>

using namespace std::filesystem;
using namespace nframework::log4nf;
int main()
{
    NIntegrator* nIntegrator = &(NIntegrator::getInstance());
    Loggable l{ L"Main" };

    IniHandler iniHandler;
    
    std::wstringstream s; s << L"MiniProject " << L"[" << __FUNCTIONW__ << L"] " ;
    l.info(s); s.str(L"");

    iniHandler.readIni(L"MiniProject.ini");

    if (iniHandler.readString(L"nLogger", L"USE") == L"true")
    {
        nIntegrator->activateNLogger();
    }
    else
    {
        // else
    }

    if ( iniHandler.readString(L"SchemaRegistryData" , L"USE") == L"true" )
    {
        std::wstring srPath = iniHandler.readString(L"SchemaRegistryData", L"PATH");
        std::wstring srXml = iniHandler.readString(L"SchemaRegistryData", L"XML");        
        bool checkMsgIDDuplication = iniHandler.readString(_T("SchemaRegistryData"), _T("CheckMsgIDDuplication")) == _T("true") ? true : false;
        srPath = srPath == L"" ? L"" : srPath + L"\\";
        srXml = srPath + srXml;
        nIntegrator->setSchemaRegistryData(srXml, checkMsgIDDuplication);
    }
    else
    {
        // else
    }

    unsigned int numOfComponents = iniHandler.readUInteger(L"Components", L"Count");

    const std::wstring origPath = current_path();

    /************************************************************************
        plug in components
    ************************************************************************/
    for (unsigned int cnt = 1; cnt <= numOfComponents; cnt++)
    {
        
        tstringstream dllPrefix;
        dllPrefix << L"Component_" << cnt;

        std::wstring dllIndex;
        dllPrefix >> dllIndex;

        std::wstring power = iniHandler.readString(dllIndex, L"POWER");
        std::wstring dllPath = iniHandler.readString(dllIndex, L"PATH");
        std::wstring dllName = iniHandler.readString(dllIndex , L"DLL");
        std::wstring nomName = iniHandler.readString(dllIndex , L"XML");

        dllPath = dllPath == L"" ? L"" : dllPath + L"\\";
        dllPath = origPath + L"\\" + dllPath;

#ifdef _DEBUG
        dllName = dllName + L"d.dll";
#else
        dllName = dllName + L".dll";
#endif // _DEBUG

        if (power == L"on") {
            current_path(dllPath);

            nIntegrator->plugInComponent(dllName, nomName);

            current_path(origPath);
        }
        else if (power == L"off") {
            s << dllName << L" Plug-in module is off. Do nothing." ;
            l.info(s); s.str(L"");
        }
        else {
            s << L"Wrong input. Do nothing." ;
            l.info(s); s.str(L"");
        }
    }

    if (iniHandler.readString(L"ValidatingComponents", L"USE") == L"true")
    {
        if (iniHandler.readString(_T("ValidatingComponents"), _T("MetadataFullValidation")) == _T("true"))
        {
            nIntegrator->validateComponentsPluggedIn(true);
        }
        else
        {
            nIntegrator->validateComponentsPluggedIn(false);
        }
    }
    else
    {
        // else
    }

    for (unsigned int cnt = 1; cnt <= numOfComponents; cnt++)
    {
        tstringstream dllPrefix;
        dllPrefix << L"Component_" << cnt;

        std::wstring dllIndex;
        dllPrefix >> dllIndex;

        std::wstring power = iniHandler.readString(dllIndex, L"POWER");
        std::wstring dllName = iniHandler.readString(dllIndex, L"DLL");

        if (power == L"on") {
            (nIntegrator->getUserManager(dllName))->start();
        }

    }

    tcin.get();

    /************************************************************************
        plug out components
    ************************************************************************/
    for (unsigned int cnt = 1; cnt <= numOfComponents; cnt++)
    {
        tstringstream dllPrefix;
        dllPrefix << L"Component_" << cnt;

        std::wstring dllIndex;
        dllPrefix >> dllIndex;

        std::wstring power = iniHandler.readString(dllIndex, L"POWER");
        std::wstring dllName = iniHandler.readString(dllIndex, L"DLL");

        if (power == L"on") {
            (nIntegrator->getUserManager(dllName))->stop();
        }
        
    }

    for (unsigned int cnt = 1; cnt <= numOfComponents; cnt++)
    {
        tstringstream dllPrefix;
        dllPrefix << L"Component_" << cnt;

        std::wstring dllIndex;
        dllPrefix >> dllIndex;

        std::wstring power = iniHandler.readString(dllIndex, L"POWER");
        std::wstring dllName = iniHandler.readString(dllIndex, L"DLL");

        if (power == L"on") {
            nIntegrator->plugOutComponent(dllName);
            s << L"Plug out " << dllName << L" module." ;
            l.info(s); s.str(L"");
        }
    }

    s << L"The End." ;
    l.info(s);
    

    return 0;
}
