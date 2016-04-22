#include <picotorrent/client/ui/property_sheets/details/options_page.hpp>

#include <picotorrent/client/i18n/translator.hpp>
#include <picotorrent/client/ui/resources.hpp>

using picotorrent::client::ui::property_sheets::details::options_page;

options_page::options_page()
{
    set_flags(PSP_USETITLE);
    set_instance(GetModuleHandle(NULL));
    set_template_id(IDD_DETAILS_OPTIONS);
    set_title(TR("options"));
}

BOOL options_page::on_command(HWND hDlg, UINT uCtrlId, WPARAM wParam, LPARAM lParam)
{
    if (!is_initializing())
    {
        check_changed(hDlg, uCtrlId, HIWORD(wParam));
    }

    switch (uCtrlId)
    {
    case ID_SEQUENTIAL_DOWNLOAD:
    {
        sequential_download(!sequential_download());
        break;
    }
    }

    return FALSE;
}

void options_page::on_init_dialog()
{
    set_dlg_item_text(ID_LIMITS_GROUP, TR("limits"));
    set_dlg_item_text(ID_DL_LIMIT_TEXT, TR("dl_limit"));
    set_dlg_item_text(ID_DL_LIMIT_HELP, TR("dl_limit_help"));
    set_dlg_item_text(ID_UL_LIMIT_TEXT, TR("ul_limit"));
    set_dlg_item_text(ID_UL_LIMIT_HELP, TR("ul_limit_help"));
    set_dlg_item_text(ID_MAX_CONNECTIONS_TEXT, TR("max_connections"));
    set_dlg_item_text(ID_MAX_CONNECTIONS_HELP, TR("max_connections_help"));
    set_dlg_item_text(ID_MAX_UPLOADS_TEXT, TR("max_uploads"));
    set_dlg_item_text(ID_MAX_UPLOADS_HELP, TR("max_uploads_help"));
    set_dlg_item_text(ID_SEQUENTIAL_DOWNLOAD, TR("sequential_download"));
}

int options_page::dl_limit()
{
    std::string text = get_dlg_item_text(ID_DL_LIMIT);
    if (text.empty()) { return -1; }
    return std::stoi(text);
}

void options_page::dl_limit(int limit)
{
    set_dlg_item_text(ID_DL_LIMIT, std::to_string(limit));
}

int options_page::ul_limit()
{
    std::string text = get_dlg_item_text(ID_UL_LIMIT);
    if (text.empty()) { return -1; }
    return std::stoi(text);
}

void options_page::ul_limit(int limit)
{
    set_dlg_item_text(ID_UL_LIMIT, std::to_string(limit));
}

int options_page::max_connections()
{
    std::string text = get_dlg_item_text(ID_MAX_CONNECTIONS);
    if (text.empty()) { return -1; }
    return std::stoi(text);
}

void options_page::max_connections(int max)
{
    set_dlg_item_text(ID_MAX_CONNECTIONS, std::to_string(max));
}

int options_page::max_uploads()
{
    std::string text = get_dlg_item_text(ID_MAX_UPLOADS);
    if (text.empty()) { return -1; }
    return std::stoi(text);
}

void options_page::max_uploads(int max)
{
    set_dlg_item_text(ID_MAX_UPLOADS, std::to_string(max));
}

bool options_page::sequential_download()
{
    return IsDlgButtonChecked(handle(), ID_SEQUENTIAL_DOWNLOAD) == BST_CHECKED;
}

void options_page::sequential_download(bool val)
{
    UINT check = val ? BST_CHECKED : BST_UNCHECKED;
    CheckDlgButton(handle(), ID_SEQUENTIAL_DOWNLOAD, check);
}

void options_page::check_changed(HWND hDlg, UINT uCtrlId, UINT uCommand)
{
    switch (uCtrlId)
    {
    case ID_DL_LIMIT:
    case ID_UL_LIMIT:
    case ID_MAX_CONNECTIONS:
    case ID_MAX_UPLOADS:
    case ID_SEQUENTIAL_DOWNLOAD:
    {
        switch (uCommand)
        {
        case BN_CLICKED:
        case EN_CHANGE:
        {
            PropSheet_Changed(GetParent(hDlg), hDlg);
            break;
        }
        }
        break;
    }
    }
}
