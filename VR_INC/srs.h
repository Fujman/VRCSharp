//
// SRS common
//
#define REGKEY_SRS_BASE               _T("SpecialRecordingSystems")
#define REGKEY_SRS_HKLM_BASE          _T("Software\\") REGKEY_SRS_BASE
#define REGKEY_SRS_HKCU_BASE          _T("Software\\") REGKEY_SRS_BASE

//
// SRS Femida Pro
//

#define REGKEY_SRS_FEMIDA_PRO         REGKEY_SRS_HKLM_BASE _T("\\SRSFemidaPro")

#define REGKEY_SRS_PORTAL_KEY         _T("PortalURL")  //                          http://srscaseflow.srsfemida.example.com
#define REGKEY_SRS_CONFIG_KEY         _T("ConfigURL")  //                          http://srscaseflow.srsfemida.example.com/femida/srs.config.xml
#define REGKEY_SRS_CACHED_PORTAL_KEY  _T("CachedPortalURL")
#define REGKEY_SRS_CACHED_CONFIG_KEY  _T("CachedConfigURL")
#define REGKEY_SRS_CACHED_CONFIG_DATA_KEY _T("CachedConfig")

#define FILE_SRS_FEMIDA_PRO_URL       _T("SRS Femida Pro.url")
#define PATH_SRS_CONFIG_XML           _T("femida/srs.config.xml")
#define FILE_SRS_CONFIG_XML           _T("srs.config.xml")
#define _FILE_SRS_SCHEDULE_TXT        _T("schedule.txt")

#define CFGKEY_SRS_PORTAL_KEY         _T("PortalURL")
#define CFGKEY_SRS_CENTRAL_KEY        _T("Storage_Records_Central") //same as REGKEY_SRS_CENTRAL_KEY   /REC=this\%server% /CENTRAL=this \\srscaseflow.srsfemida.example.com\srscentral\reports
//efine CFGKEY_SRS_CENTRAL_KEY_VIDEO  _T("Storage_Records_Central") //?                                                                 \\srscaseflow.srsfemida.example.com\srscentral\records
#define CFGKEY_SRS_NETWORK_KEY        _T("Storage_Reports_Central") //same as REGKEY_SRS_NETWORK_KEY?  /NET=this
#define CFGKEY_SRS_TEMPLATES_KEY      _T("Templates")//may be local           REGKEY_SRS_TEMPLATES_SEC\Path?  /TP=this  //OLD:Storage_Templates_Central
#define CFGKEY_SRS_COMMON_TEMPLATES_KEY _T("CommonTemplates") //may be local?

#define CFGKEY_SRS_REPORTS_FLAGS_KEY  _T("Storage_Reports_Flags") //"disable_video" - config only
#define CFGKEY_SRS_MULTIUSERMODE_KEY  _T("Storage_Reports_Mode")  //"domain,multiuser"

#define CFGKEY_SRS_RECORDS_AUTOPURGE  _T("Storage_Records_AutoPurge") //"on"/"off"
#define CFGKEY_SRS_RECORDS_KEEPDAYS   _T("Storage_Records_KeepDays")   //int
#define CFGKEY_SRS_RECORDS_FREEPART   _T("Storage_Records_FreePart")//int, %

//
// SRS common (obsolete, but still using)
//

#define REGKEY_SRS_RECORDS            REGKEY_SRS_HKLM_BASE _T("\\CourtProtocol\\VR_COURT.INI\\SRSRegistrator") //"AudioRecords","VideoRecords" //records only
#define REGKEY_SRS_REPORTS            REGKEY_SRS_HKLM_BASE _T("\\CourtProtocol\\VR_COURT.INI\\Archiving")      //"ArchivePath","CDRWPath"      //reports+records

#define REGKEY_SRS_NETWORK            REGKEY_SRS_HKLM_BASE _T("\\CourtProtocol\\VR_COURT.INI\\Archiving")      //"NetworkPath"    //reports+records by users //HKCU doubled
#define REGKEY_SRS_CENTRAL            REGKEY_SRS_HKLM_BASE _T("\\CourtProtocol\\VR_COURT.INI\\SRSRegistrator") //"NetworkStorage" //records only by servers

#define REGKEY_SRS_RECORDS_SEC        _T("SRSRegistrator")
#define REGKEY_SRS_REPORTS_SEC        _T("Archiving")
#define REGKEY_SRS_CENTRAL_SEC        _T("SRSRegistrator")

#define REGKEY_SRS_RECORDS_KEY        _T("AudioRecords")
#define REGKEY_SRS_RECORDS_KEY_VIDEO  _T("VideoRecords")
#define REGKEY_SRS_REPORTS_KEY        _T("ArchivePath")
#define REGKEY_SRS_NETWORK_KEY        _T("NetworkPath")             //same as CFGKEY_SRS_NETWORK_KEY   /NET=this or /NET=this\.. (%user% added manually)
#define REGKEY_SRS_CENTRAL_KEY        _T("NetworkStorage")          //same as CFGKEY_SRS_CENTRAL_KEY   /REC=this\%server% and /CENTRAL=this
#define REGKEY_SRS_MULTIUSERMODE_KEY  _T("MultiUserMode") //"domain", in REGKEY_SRS_REPORTS
#define REGKEY_SRS_REPORTS_FLAGS_KEY  _T("Storage_Reports_Flags") //"disable_video"

#define REGKEY_SRS_TEMPLATES          REGKEY_SRS_HKCU_BASE _T("\\CourtProtocol\\VR_COURT.INI\\Templates")
#define REGKEY_SRS_TEMPLATES_SEC      _T("Templates")
#define REGKEY_SRS_TEMPLATES_KEY      _T("Path")

//
// VrServer   #define REGKEY_BASE _T("SpecialRecordingSystems\\SRSRegistrator") -> REGKEY_BASE_REGISTRATOR
//            #define REGKEY_HKLM _T("SpecialRecordingSystems")                 -> REGKEY_SRS_BASE

#define REGKEY_BASE_REGISTRATOR REGKEY_SRS_BASE      _T("\\SRSRegistrator")
#define REGKEY_INI_REGISTRATOR  REGKEY_SRS_HKCU_BASE _T("\\SRSRegistrator\\VrServer.INI")

#define REGKEY_HW_REGISTRATOR   REGKEY_SRS_HKLM_BASE _T("\\Hardware") //              "Software\\SpecialRecordingSystems\\Hardware"
#define REGKEY_HKLM_REGISTRATOR REGKEY_SRS_HKLM_BASE _T("\\SRSRegistrator") //        "Software\\SpecialRecordingSystems\\SRSRegistrator"//AY 16.11.2011

//            #define DEVKEY_BASE _T("SpecialRecordingSystems\\VR_COURT")       -> DEVKEY_BASE_VR_COURT
// VR_COURT   #define REGKEY_BASE _T("SpecialRecordingSystems\\CourtProtocol")  -> REGKEY_BASE_VR_COURT
//            #define REGKEY_INI  _T("SOFTWARE\\SpecialRecordingSystems\\CourtProtocol\\VR_COURT.INI") ->REGKEY_INI_VR_COURT

#define REGKEY_BASE_VR_COURT    REGKEY_SRS_BASE      _T("\\CourtProtocol")
#define REGKEY_INI_VR_COURT     REGKEY_SRS_HKCU_BASE _T("\\CourtProtocol\\VR_COURT.INI")

#define DEVKEY_BASE_VR_COURT    REGKEY_SRS_BASE      _T("\\VR_COURT")
#define REGKEY_HW_VR_COURT      REGKEY_SRS_HKLM_BASE _T("\\VR_COURT\\Hardware") //    "Software\\SpecialRecordingSystems\\VR_Court\\Hardware"

//            //HKEY_CURRENT_USER\\Software\\SpecialRecordingSystems\\SRSAuBackup"//same as in VR_COURT
// AuBackup   #define REGKEY_BASE "SpecialRecordingSystems\\SRSAuBackup"        -> REGKEY_BASE_AUBACKUP
//
#define REGKEY_BASE_AUBACKUP    REGKEY_SRS_BASE      _T("\\SRSAuBackup")
#define REGKEY_INI_AUBACKUP     REGKEY_SRS_HKCU_BASE _T("\\SRSAuBackup\\AuBackup.INI")

#define REGKEY_HW_AUBACKUP      REGKEY_SRS_HKCU_BASE _T("\\SRSAuBackup\\Hardware") // "Software\\SpecialRecordingSystems\\SRSAuBackup\\Hardware"

//
// SRSDiag
//
//#define REGKEY_BASE "SpecialRecordingSystems\\SRSDiagnostics"
#define REGKEY_BASE_DIAGNOSTICS REGKEY_SRS_BASE      _T("\\SRSDiagnostics")
#define REGKEY_INI_DIAGNOSTICS  REGKEY_SRS_HKCU_BASE _T("\\SRSDiagnostics\\SRSDiag.INI")
//
// configurations:
//
//      REGKEY_HW_REGISTRATOR   REGKEY_SRS_HKLM_BASE _T("\\Hardware")           //    "Software\\SpecialRecordingSystems\\Hardware"
//      REGKEY_HW_VR_COURT      REGKEY_SRS_HKLM_BASE _T("\\VR_COURT\\Hardware") //    "Software\\SpecialRecordingSystems\\VR_Court\\Hardware"
#define REGKEY_HW_SRSTV         REGKEY_SRS_HKCU_BASE _T("\\SRSTV\\Hardware")    //    "Software\\SpecialRecordingSystems\\SRSTV\\Hardware"
#define REGKEY_HW_SRSPLAYER     REGKEY_SRS_HKCU_BASE _T("\\SRSPlayer\\Hardware")//    "Software\\SpecialRecordingSystems\\SRSPlayer\\Hardware"
