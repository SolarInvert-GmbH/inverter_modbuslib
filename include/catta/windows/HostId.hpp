#pragma once

// system
#include <comdef.h>
#include <ntddscsi.h>
#include <wbemidl.h>
#include <windows.h>

// std
#include <optional>

namespace catta
{
namespace windows
{

/**
 * @brief Class to get an id to identify the host pc.
 * @author CattaTech - Maik Urbannek
 */
class HostId
{
  public:
    /**
     * @return Returns a id to identify the host pc. In this case the processor id.
     */
    static std::optional<std::uint64_t> get()
    {
        const wchar_t* ServerName = L"ROOT\\CIMV2";
        const wchar_t* Field = L"ProcessorId";
        const wchar_t* Query = L"SELECT ProcessorId FROM Win32_Processor";

        IWbemLocator* Locator{};
        IWbemServices* Services{};
        IEnumWbemClassObject* Enumerator{};
        IWbemClassObject* ClassObject{};
        VARIANT Variant{};
        DWORD Returned{};

        const auto close = [&Services, &Locator, &Enumerator](const auto i)
        {
            if (i >= 3) Services->Release();
            if (i >= 2) Locator->Release();
            if (i >= 1) Enumerator->Release();
            if (i >= 0) CoUninitialize();
        };
        const auto failed = [close](const auto i)
        {
            close(i);
            return std::optional<std::uint64_t>{};
        };

        if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) return failed(0);

        if (FAILED(CoInitializeSecurity(nullptr, -1, nullptr, nullptr, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE,
                                        nullptr)))
            return failed(1);

        if (FAILED(CoCreateInstance(CLSID_WbemLocator, NULL, CLSCTX_INPROC_SERVER, IID_IWbemLocator, reinterpret_cast<PVOID*>(&Locator))))
            return failed(1);

        if (FAILED(Locator->ConnectServer(_bstr_t(ServerName), nullptr, nullptr, nullptr, 0, nullptr, nullptr, &Services))) return failed(2);

        if (FAILED(CoSetProxyBlanket(Services, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE,
                                     nullptr, EOAC_NONE)))
            return failed(3);

        if (FAILED(Services->ExecQuery(bstr_t(L"WQL"), bstr_t(Query), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &Enumerator)))
            return failed(3);

        std::size_t i = 0;
        while (Enumerator)
        {
            Enumerator->Next(static_cast<LONG>(WBEM_INFINITE), 1, &ClassObject, &Returned);

            const auto clear = [&Variant, &ClassObject]()
            {
                VariantClear(&Variant);
                ClassObject->Release();
            };

            if (!Returned)
            {
                break;
            }

            ClassObject->Get(Field, 0, &Variant, nullptr, nullptr);
            if (i == 0)
            {
                const wchar_t* s = reinterpret_cast<wchar_t*>((static_cast<bstr_t>(Variant.bstrVal)).copy());
                if (s)
                {
                    std::uint64_t r = 0;
                    for (const wchar_t* p = s; *p != '\0'; p++)
                    {
                        const wchar_t c = *p;
                        const std::uint64_t h = c >= '0' && c <= '9'   ? static_cast<wchar_t>(c - '0')
                                                : c >= 'a' && c <= 'f' ? static_cast<wchar_t>(c - 'a' + 10)
                                                : c >= 'A' && c <= 'F' ? static_cast<wchar_t>(c - 'A' + 10)
                                                                       : 16;
                        if (h < 16) r = (r << 4) | h;
                    }
                    clear();
                    close(3);
                    return std::optional<std::uint64_t>{r};
                }
            }
            clear();
            i++;
        }

        return failed(3);
    }
};
}  // namespace windows
}  // namespace catta
