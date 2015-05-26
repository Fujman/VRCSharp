//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
// Define the severity codes
//
//
// Define the facility codes
//
//
//
//
// Strings
//

//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define FACILITY_STRINGS                 0x78
#define FACILITY_EVENT                   0x76
#define FACILITY_DIALOG                  0x75


//
// Define the severity codes
//
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_ERROR            0x3
#define STATUS_SEVERITY_DESCRIPTION      0x1


//
// MessageId: IDSX_BASE_IDENTIFIER
//
// MessageText:
//
//  ?
//
#define IDSX_BASE_IDENTIFIER             0x40780000L

//
// MessageId: IDSX_LAST_IDENTIFIER
//
// MessageText:
//
//  
//
#define IDSX_LAST_IDENTIFIER             0x4078FFFFL

//--------------------------------------------------------------------------
//
// Predefined ID's
//

//
// MessageId: IDSX_LANGUAGE_NAME
//
// MessageText:
//
//  English
//
#define IDSX_LANGUAGE_NAME               0x40780001L

//
// MessageId: IDSX_FONTS_MAPPING
//
// MessageText:
//
//  
//
#define IDSX_FONTS_MAPPING               0x40780002L

//
// MessageId: IDSX_STANDARD_WORDS
//
// MessageText:
//
//  OK\nCancel\nAbort\nRetry\nIgnore\nYes\nNo\nClose\nHelp\nApply\nRevert\nDefaults\nOpen\nSave\nSave As
//
#define IDSX_STANDARD_WORDS              0x40780003L

//
// MessageId: IDSX_SELECT_LANGUAGE
//
// MessageText:
//
//  Select language
//
#define IDSX_SELECT_LANGUAGE             0x4078000FL

// About dialog
//
// MessageId: IDSX_IDC_STATIC_PRODUCT
//
// MessageText:
//
//  SRSR Court recorder
//
#define IDSX_IDC_STATIC_PRODUCT          0x40780100L

//
// MessageId: IDSX_IDC_STATIC_COPYRIGHT
//
// MessageText:
//
//  Copyright c Special Recording Systems. Ltd. 2001-2014, all rights reserved.
//
#define IDSX_IDC_STATIC_COPYRIGHT        0x40780101L

//
// MessageId: IDSX_IDC_STATIC_LICENSED
//
// MessageText:
//
//  This software licensed to:
//
#define IDSX_IDC_STATIC_LICENSED         0x40780102L

//
// MessageId: IDSX_IDC_STATIC_WARNING
//
// MessageText:
//
//  ATTENTION! This computer program is protected by copyright law and international treaties. Unauthorized reproduction or distribution of this program, or any portion of it, may result in severe civil and criminal penalties.
//
#define IDSX_IDC_STATIC_WARNING          0x40780103L

//
// MessageId: IDSX_IDC_STATIC_CONTACTS
//
// MessageText:
//
//  Contacts and technical support:
//
#define IDSX_IDC_STATIC_CONTACTS         0x40780104L

//
// MessageId: IDSX_IDC_STATIC_PHONE
//
// MessageText:
//
//  Phone:        +380(44) 248-79-91
//
#define IDSX_IDC_STATIC_PHONE            0x40780105L

//
// MessageId: IDSX_IDC_STATIC_PHONEFAX
//
// MessageText:
//
//  Phone/fax:  +380(44) 248-79-90
//
#define IDSX_IDC_STATIC_PHONEFAX         0x40780106L

// SRSFemida - common
//
// MessageId: IDSX_IDS_COL_TIME
//
// MessageText:
//
//  Time
//
#define IDSX_IDS_COL_TIME                0x407805DCL

//
// MessageId: IDSX_IDS_COL_ACTION
//
// MessageText:
//
//  Action
//
#define IDSX_IDS_COL_ACTION              0x407805DDL

//
// MessageId: IDSX_IDS_COL_PERSONE
//
// MessageText:
//
//  Participant
//
#define IDSX_IDS_COL_PERSONE             0x407805DEL

//
// MessageId: IDSX_IDS_COL_NOTES
//
// MessageText:
//
//  Note
//
#define IDSX_IDS_COL_NOTES               0x407805DFL

//
// MessageId: IDSX_IDS_CASE_NUMBER
//
// MessageText:
//
//  Case number:
//
#define IDSX_IDS_CASE_NUMBER             0x407805E0L

//
// MessageId: IDSX_IDS_QUERY_NEW_TEMPLATE
//
// MessageText:
//
//  Open a new case type based on \"%s\" ?
//
#define IDSX_IDS_QUERY_NEW_TEMPLATE      0x407805E6L

//
// MessageId: IDSX_IDS_QUERY_DELETE_TEMPLATE
//
// MessageText:
//
//  Do you want to remove this type of case  \"%s\" ?
//
#define IDSX_IDS_QUERY_DELETE_TEMPLATE   0x407805E7L

//
// MessageId: IDSX_IDS_QUERY_START
//
// MessageText:
//
//  Mode selection
//
#define IDSX_IDS_QUERY_START             0x407805E8L

//
// MessageId: IDSX_IDS_QUERY_STOP_RECORD
//
// MessageText:
//
//  Record is in progress. Would you like to exit without stopping it?
//
#define IDSX_IDS_QUERY_STOP_RECORD       0x407805E9L

//
// MessageId: IDSX_IDS_QUERY_IMPORT_PERSONES
//
// MessageText:
//
//  Would you like to import the list of participants from the previous trial? 
//
#define IDSX_IDS_QUERY_IMPORT_PERSONES   0x407805EAL

//
// MessageId: IDSX_IDS_ENTER_MEDIA_NUMBER
//
// MessageText:
//
//  Enter the media (CD-R) serial number:
//
#define IDSX_IDS_ENTER_MEDIA_NUMBER      0x407805EBL

//
// MessageId: IDSX_IDS_QUERY_BUSINESS_EXISTS
//
// MessageText:
//
//  This case already exists!
//
#define IDSX_IDS_QUERY_BUSINESS_EXISTS   0x407805ECL

//
// MessageId: IDSX_IDS_TEMPLATE_NAME_CONFLICT
//
// MessageText:
//
//  This template already exists. \n Do you want to overwrite or copy it?
//
#define IDSX_IDS_TEMPLATE_NAME_CONFLICT  0x407805EDL

//
// MessageId: IDSX_IDS_TEMPLATE_SAVE
//
// MessageText:
//
//  Do you want to save template? 
//
#define IDSX_IDS_TEMPLATE_SAVE           0x407805EEL

//
// MessageId: IDSX_IDS_USE_SIGNATURE
//
// MessageText:
//
//  Use digital signature
//
#define IDSX_IDS_USE_SIGNATURE           0x407805EFL

//
// MessageId: IDSX_IDS_QUERY_KILL_BACKUP
//
// MessageText:
//
//  A backup copy will be completely removed! Would you like to continue? 
//
#define IDSX_IDS_QUERY_KILL_BACKUP       0x407805F0L

//
// MessageId: IDSX_IDS_ERROR_EDITOR_CALL
//
// MessageText:
//
//  Text editor is not found!\n%s
//
#define IDSX_IDS_ERROR_EDITOR_CALL       0x40780618L

//
// MessageId: IDSX_IDS_ERROR_MAKE_FILE
//
// MessageText:
//
//  The file cannot be created\n%s\nClose all windows with this document.
//
#define IDSX_IDS_ERROR_MAKE_FILE         0x40780619L

//
// MessageId: IDSX_IDS_QUERY_DISABLE_VIDEO
//
// MessageText:
//
//  Video server is not found. Would you like to disable video features?
//
#define IDSX_IDS_QUERY_DISABLE_VIDEO     0x4078061AL

//
// MessageId: IDSX_IDS_QUERY_OVERWRITE
//
// MessageText:
//
//  Do you want to overwrite?
//
#define IDSX_IDS_QUERY_OVERWRITE         0x4078061BL

//
// MessageId: IDSX_IDS_QUERY_WORK_OFFLINE
//
// MessageText:
//
//  Work offline?
//
#define IDSX_IDS_QUERY_WORK_OFFLINE      0x4078061CL

//
// MessageId: IDSX_IDS_MESSAGE_WORK_OFFLINE
//
// MessageText:
//
//  Offline work
//
#define IDSX_IDS_MESSAGE_WORK_OFFLINE    0x4078061DL

//
// MessageId: IDSX_IDS_MESSAGE_UNKNOWN_VERSION_LOADED
//
// MessageText:
//
//  Unknown version of the file will be loaded from disk
//
#define IDSX_IDS_MESSAGE_UNKNOWN_VERSION_LOADED 0x4078061EL

//
// MessageId: IDSX_IDS_QUERY_SELECT_VERSION
//
// MessageText:
//
//  Select version
//
#define IDSX_IDS_QUERY_SELECT_VERSION    0x4078061FL

//
// MessageId: IDSX_IDS_MESSAGE_VERSION_LOCKED
//
// MessageText:
//
//  Version %d is already open. Close it, or ask your system administrator to unlock version.
//
#define IDSX_IDS_MESSAGE_VERSION_LOCKED  0x40780620L

//
// MessageId: IDSX_IDS_MESSAGE_ON_LANGUAGE_SELECT
//
// MessageText:
//
//  Restart the program for the interface language changes to take effect.
//
#define IDSX_IDS_MESSAGE_ON_LANGUAGE_SELECT 0x40780640L

//
// MessageId: IDSX_IDS_MESSAGE_LOCKED_DURING_RECORDING
//
// MessageText:
//
//  This operation cannot be performed while recording.
//
#define IDSX_IDS_MESSAGE_LOCKED_DURING_RECORDING 0x40780641L

//
// MessageId: IDSX_IDS_MESSAGE_PREVIOUS_TRIAL_NOT_FOUND
//
// MessageText:
//
//  Previous trials cannot be found. 
//
#define IDSX_IDS_MESSAGE_PREVIOUS_TRIAL_NOT_FOUND 0x40780642L

//
// MessageId: IDSX_IDS_OUT_OF_LICENSE
//
// MessageText:
//
//  Out of license
//
#define IDSX_IDS_OUT_OF_LICENSE          0x40780643L

//
// MessageId: IDSX_IDS_BUSINESS_WORD
//
// MessageText:
//
//  Case #
//
#define IDSX_IDS_BUSINESS_WORD           0x407807BCL

//
// MessageId: IDSX_IDS_SESSION_WORD
//
// MessageText:
//
//  Date
//
#define IDSX_IDS_SESSION_WORD            0x407807BDL

//
// MessageId: IDSX_IDS_NAME_WORD
//
// MessageText:
//
//  Name
//
#define IDSX_IDS_NAME_WORD               0x407807BEL

//
// MessageId: IDSX_IDS_NAME_WORD2
//
// MessageText:
//
//  Accused in /charged with:
//
#define IDSX_IDS_NAME_WORD2              0x407807BFL

//
// MessageId: IDSX_IDS_WORD_SIZE
//
// MessageText:
//
//  Size
//
#define IDSX_IDS_WORD_SIZE               0x407807C0L

//
// MessageId: IDSX_IDS_SIZE_FORMAT1
//
// MessageText:
//
//  %s, %d records, %d dirs
//
#define IDSX_IDS_SIZE_FORMAT1            0x407807C1L

//
// MessageId: IDSX_IDS_SIZE_FORMAT2
//
// MessageText:
//
//  %s, %d records
//
#define IDSX_IDS_SIZE_FORMAT2            0x407807C2L

//
// MessageId: IDSX_IDS_SIZE_FORMAT3
//
// MessageText:
//
//  %s
//
#define IDSX_IDS_SIZE_FORMAT3            0x407807C3L

//
// MessageId: IDSX_IDS_KB
//
// MessageText:
//
//  kB
//
#define IDSX_IDS_KB                      0x407807C4L

//
// MessageId: IDSX_IDS_MB
//
// MessageText:
//
//  MB
//
#define IDSX_IDS_MB                      0x407807C5L

//
// MessageId: IDSX_IDS_GB
//
// MessageText:
//
//  GB
//
#define IDSX_IDS_GB                      0x407807C6L

//
// MessageId: IDSX_IDS_WORD_TYPE
//
// MessageText:
//
//  Type
//
#define IDSX_IDS_WORD_TYPE               0x407807C7L

//
// MessageId: IDSX_IDS_BUSINESS_FILENAME_FORMAT
//
// MessageText:
//
//  Case #%s from %s
//
#define IDSX_IDS_BUSINESS_FILENAME_FORMAT 0x407807CFL

//
// MessageId: IDSX_IDS_BUSINESS_TITLE_FORMAT
//
// MessageText:
//
//  Case #%s from %s
//
#define IDSX_IDS_BUSINESS_TITLE_FORMAT   0x407807D0L

//
// MessageId: IDSX_IDS_CURRENT_TEMPLATE
//
// MessageText:
//
//  <<<current>>>
//
#define IDSX_IDS_CURRENT_TEMPLATE        0x407807D1L

//
// MessageId: IDSX_IDS_RECORDING_START
//
// MessageText:
//
//  <<<recording start>>>
//
#define IDSX_IDS_RECORDING_START         0x407807D2L

//
// MessageId: IDSX_IDS_RECORDING_STOP
//
// MessageText:
//
//  <<<recording stop>>>
//
#define IDSX_IDS_RECORDING_STOP          0x407807D3L

//
// MessageId: IDSX_IDS_WORD_COPY
//
// MessageText:
//
//   [Copy %d]
//
#define IDSX_IDS_WORD_COPY               0x407807D4L

//
// MessageId: IDSX_IDS_WORD_INTERNAL
//
// MessageText:
//
//  *
//
#define IDSX_IDS_WORD_INTERNAL           0x407807D5L

//
// MessageId: IDSX_IDS_DOCUMENT_VARIABLES_LOCALIZED
//
// MessageText:
//
//  number\ndate\nname\nnumroom\nvolume\nstart\nfinish\naudiorecording journal\nactual persones\nsignature\nserial number\ndate_local\n
//
#define IDSX_IDS_DOCUMENT_VARIABLES_LOCALIZED 0x407807D6L

//
// MessageId: IDSX_IDS_DOCUMENT_BODY_VARIABLE_LOCALIZED
//
// MessageText:
//
//  time\naction\nperson\nnote\ndate_local\n
//
#define IDSX_IDS_DOCUMENT_BODY_VARIABLE_LOCALIZED 0x407807D7L

//
// MessageId: IDSX_IDS_DOCUMENT_VARIABLES
//
// MessageText:
//
//  number\ndate\nname\nnumroom\nvolume\nstart\nfinish\naudiorecording journal\nactual persones\nsignature\nserial number\ndate_local\n
//
#define IDSX_IDS_DOCUMENT_VARIABLES      0x407807D8L

//
// MessageId: IDSX_IDS_DOCUMENT_BODY_VARIABLE
//
// MessageText:
//
//  time\naction\nperson\nnote\ndate_local\n
//
#define IDSX_IDS_DOCUMENT_BODY_VARIABLE  0x407807D9L

//
// MessageId: IDSX_IDS_CHOOSE_FOLDER
//
// MessageText:
//
//  Please select folder for trial documents.
//
#define IDSX_IDS_CHOOSE_FOLDER           0x407807DDL

//
// MessageId: IDSX_IDS_OK_CANCEL
//
// MessageText:
//
//  OK\nCancel\n
//
#define IDSX_IDS_OK_CANCEL               0x407807DFL

//
// MessageId: IDSX_IDS_BUTTONS_TEMPLATE_ACTIONS
//
// MessageText:
//
//  New action (Ins)\nDelete action (Del)\nEdit action (Alt + F2)\nIncrease level (Alt + <-)\nDecrease level (Alt + ->)\nMove up (Alt + Up)\nMove down (Alt + Down)\nAdd format of the paragraph (Alt + Ins)\nDelete format of the paragraph (Alt + Del)\n
//
#define IDSX_IDS_BUTTONS_TEMPLATE_ACTIONS 0x407807E0L

//
// MessageId: IDSX_IDS_BUTTONS_TEMPLATE_PERSONES
//
// MessageText:
//
//  New person (Ins)\nDelete person (Del)\nEdit (Alt + F2)\nEdit preview (Alt+F3)\nInsert as variable (Alt + Enter)\n
//
#define IDSX_IDS_BUTTONS_TEMPLATE_PERSONES 0x407807E1L

//
// MessageId: IDSX_IDS_BUTTONS_TEMPLATE_AUTO
//
// MessageText:
//
//  Edit preview (Alt+F3)\nInsert as variable (Alt + Enter)\n
//
#define IDSX_IDS_BUTTONS_TEMPLATE_AUTO   0x407807E2L

//
// MessageId: IDSX_IDS_BUTTONS_TEMPLATE_FORMATTING
//
// MessageText:
//
//  Font\nFont size\nZoom\nText\nText by condition: all variables\nText by condition: any variable\nBold\nItalic\nUnderlined\nFlush left\nFlush center\nFlush right\nFlush justify\nMarked list\nSuperscript\nSubscript\n
//
#define IDSX_IDS_BUTTONS_TEMPLATE_FORMATTING 0x407807E3L

//
// MessageId: IDSX_IDS_INPUT_TEMPLATE_NAME
//
// MessageText:
//
//  Template renaming\nPlease enter a new name:
//
#define IDSX_IDS_INPUT_TEMPLATE_NAME     0x407807E4L

//
// MessageId: IDSX_IDS_DOCUMENT_VARIABLES_LOCALIZED_TRANSLATED
//
// MessageText:
//
//  number\ndate\nname\nnumroom\nvolume\nstart\nfinish\naudiorecording journal\nactual persones\nsignature\nserial number\n
//
#define IDSX_IDS_DOCUMENT_VARIABLES_LOCALIZED_TRANSLATED 0x407807EEL

//
// MessageId: IDSX_IDS_DOCUMENT_BODY_VARIABLE_LOCALIZED_TRANSLATED
//
// MessageText:
//
//  time\naction\nperson\nnote\n
//
#define IDSX_IDS_DOCUMENT_BODY_VARIABLE_LOCALIZED_TRANSLATED 0x407807EFL

//
// MessageId: IDSX_IDS_COMBO_ARCHIVE_PERIOD
//
// MessageText:
//
//  15 15 seconds\n30 30 seconds\n60 60 seconds\n120 2 minutes\n300 5 minutes\n600 10 minutes
//
#define IDSX_IDS_COMBO_ARCHIVE_PERIOD    0x40780BB8L

//
// MessageId: IDSX_IDS_COMBO_CDRW_PERIOD
//
// MessageText:
//
//  300 5 minutes\n600 10 minutes\n1800 30 minutes\n3600 1 hour
//
#define IDSX_IDS_COMBO_CDRW_PERIOD       0x40780BB9L

//
// MessageId: IDSX_IDS_COMBO_TIMEOUT
//
// MessageText:
//
//  100 0.1 seconds\n250 0.25 seconds\n500 0.5 seconds\n750 0.75 seconds\n1000 1 seconds
//
#define IDSX_IDS_COMBO_TIMEOUT           0x40780BBAL

//
// MessageId: IDSX_IDS_WORD_READONLY
//
// MessageText:
//
//  (read only)
//
#define IDSX_IDS_WORD_READONLY           0x40780BBBL

// SRSFemida - common (player)
//
// MessageId: IDSX_IDS_PLAYER_SPEED_TOOLTIPS
//
// MessageText:
//
//  100%% - Normal speed\n%d%% - Speedup to %3.1lf times\n%d%% - Deceleration in %3.1lf times
//
#define IDSX_IDS_PLAYER_SPEED_TOOLTIPS   0x40780BEAL

//
// MessageId: IDSX_IDS_PLAYER_VOLUME_TOOLTIPS
//
// MessageText:
//
//  Volume - %d%%
//
#define IDSX_IDS_PLAYER_VOLUME_TOOLTIPS  0x40780BEBL

//
// MessageId: IDSX_IDS_PLAYER_MASTER_VOLUME_TOOLTIPS
//
// MessageText:
//
//  Master volume - %d%%
//
#define IDSX_IDS_PLAYER_MASTER_VOLUME_TOOLTIPS 0x40780BECL

//
// MessageId: IDSX_IDS_PLAYER_CONTROL_SPEED_TOOLTIPS
//
// MessageText:
//
//  Speed control
//
#define IDSX_IDS_PLAYER_CONTROL_SPEED_TOOLTIPS 0x40780BEDL

//
// MessageId: IDSX_IDS_PLAYER_CONTROL_VOLUME_TOOLTIPS
//
// MessageText:
//
//  Control of channel %d. Right-click to tune.
//
#define IDSX_IDS_PLAYER_CONTROL_VOLUME_TOOLTIPS 0x40780BEEL

//
// MessageId: IDSX_IDS_PLAYER_CONTROL_MASTER_VOLUME_TOOLTIPS
//
// MessageText:
//
//  Playback control. Right-click to tune.
//
#define IDSX_IDS_PLAYER_CONTROL_MASTER_VOLUME_TOOLTIPS 0x40780BEFL

//
// MessageId: IDSX_IDS_PLAYER_CONTROL_AGC
//
// MessageText:
//
//  Auto Gain Control.\nDepth: %d dB\nThreshold: %d%%\nSpeed of reaction: %d%%\nAuto Gain Control: %s
//
#define IDSX_IDS_PLAYER_CONTROL_AGC      0x40780BF0L

//
// MessageId: IDSX_IDS_PLAYER_CONTROL_AGC_PREDEFINED
//
// MessageText:
//
//  User\nDefault\n6dB max\n20dB max
//
#define IDSX_IDS_PLAYER_CONTROL_AGC_PREDEFINED 0x40780BF1L

//
// MessageId: IDSX_IDS_PLAYER_CONTROL_EQUALIZER
//
// MessageText:
//
//  Equalizer.\n%d dB - %s\nEqualizer: %s
//
#define IDSX_IDS_PLAYER_CONTROL_EQUALIZER 0x40780BF2L

//
// MessageId: IDSX_IDS_PLAYER_CONTROL_EQUALIZER_PREDEFINED
//
// MessageText:
//
//  User\nDefault\nVoice\nRemove 50 Hz
//
#define IDSX_IDS_PLAYER_CONTROL_EQUALIZER_PREDEFINED 0x40780BF3L

//
// MessageId: IDSX_IDS_PLAYER_CONTROL_EQUALIZER_NAMES
//
// MessageText:
//
//  Low (%dHz)\nLow middle (%dHz)\nMiddle (%dHz)\nHigh middle (%dHz)\nHigh (%dHz)
//
#define IDSX_IDS_PLAYER_CONTROL_EQUALIZER_NAMES 0x40780BF4L

//
// MessageId: IDSX_IDS_PLAYER_CONTROL_EQUALIZER_PREDEFINED2
//
// MessageText:
//
//  User\nDefault\nVoice\nRemove 50 Hz\nPresence\nBrightness\nArticulation
//
#define IDSX_IDS_PLAYER_CONTROL_EQUALIZER_PREDEFINED2 0x40780BF6L

//
// MessageId: IDSX_IDS_PLAYER_CONTROL_PROCESSING
//
// MessageText:
//
//  Sound Processing.\n%d dB\nProcessing: %s
//
#define IDSX_IDS_PLAYER_CONTROL_PROCESSING 0x40780BF7L

//
// MessageId: IDSX_IDS_PLAYER_CONTROL_PROCESSING_HZCLICKSTIMBRE
//
// MessageText:
//
//  Hz\nClicks\nNormalize Tone\nSignal Processing\nAdvanced...
//
#define IDSX_IDS_PLAYER_CONTROL_PROCESSING_HZCLICKSTIMBRE 0x40780BF8L

// SRSBase.lib (player, IDSX_ only)
//
// MessageId: IDSX_IDS_AUDIO_PLAYER
//
// MessageText:
//
//  SRS Audio Player
//
#define IDSX_IDS_AUDIO_PLAYER            0x40780BFFL

//
// MessageId: IDSX_IDS_VIDEO_PLAYER
//
// MessageText:
//
//  SRS Video Player
//
#define IDSX_IDS_VIDEO_PLAYER            0x40780C00L

//
// MessageId: IDSX_IDS_VIDEO_PREVIEW
//
// MessageText:
//
//  SRS Video Preview
//
#define IDSX_IDS_VIDEO_PREVIEW           0x40780C01L

//
// MessageId: IDSX_IDS_CAMERA_INSIDE
//
// MessageText:
//
//  &Docked
//
#define IDSX_IDS_CAMERA_INSIDE           0x40780C02L

//
// MessageId: IDSX_IDS_CAMERA_OUTSIDE
//
// MessageText:
//
//  &Undocked
//
#define IDSX_IDS_CAMERA_OUTSIDE          0x40780C03L

//
// MessageId: IDSX_IDS_CAMERA_FULL_SCREEN
//
// MessageText:
//
//  &Full Screen
//
#define IDSX_IDS_CAMERA_FULL_SCREEN      0x40780C04L

// FS.lib (IMAPI2 events texts)
//
// MessageId: IDSX_IDS_IMAPI_FORMAT2_DATA_WRITE_ACTION_VALIDATING_MEDIA
//
// MessageText:
//
//  Validating current media...
//
#define IDSX_IDS_IMAPI_FORMAT2_DATA_WRITE_ACTION_VALIDATING_MEDIA 0x40780C10L

//
// MessageId: IDSX_IDS_IMAPI_FORMAT2_DATA_WRITE_ACTION_FORMATTING_MEDIA
//
// MessageText:
//
//  Formatting media...
//
#define IDSX_IDS_IMAPI_FORMAT2_DATA_WRITE_ACTION_FORMATTING_MEDIA 0x40780C11L

//
// MessageId: IDSX_IDS_IMAPI_FORMAT2_DATA_WRITE_ACTION_INITIALIZING_HARDWARE
//
// MessageText:
//
//  Initializing hardware...
//
#define IDSX_IDS_IMAPI_FORMAT2_DATA_WRITE_ACTION_INITIALIZING_HARDWARE 0x40780C12L

//
// MessageId: IDSX_IDS_IMAPI_FORMAT2_DATA_WRITE_ACTION_CALIBRATING_POWER
//
// MessageText:
//
//  Optimizing laser intensity...
//
#define IDSX_IDS_IMAPI_FORMAT2_DATA_WRITE_ACTION_CALIBRATING_POWER 0x40780C13L

//
// MessageId: IDSX_IDS_IMAPI_FORMAT2_DATA_WRITE_ACTION_WRITING_DATA
//
// MessageText:
//
//  Writing data...
//
#define IDSX_IDS_IMAPI_FORMAT2_DATA_WRITE_ACTION_WRITING_DATA 0x40780C14L

//
// MessageId: IDSX_IDS_IMAPI_FORMAT2_DATA_WRITE_ACTION_FINALIZATION
//
// MessageText:
//
//  Finalizing writing...
//
#define IDSX_IDS_IMAPI_FORMAT2_DATA_WRITE_ACTION_FINALIZATION 0x40780C15L

//
// MessageId: IDSX_IDS_IMAPI_FORMAT2_DATA_WRITE_ACTION_COMPLETED
//
// MessageText:
//
//  Completed!
//
#define IDSX_IDS_IMAPI_FORMAT2_DATA_WRITE_ACTION_COMPLETED 0x40780C16L

//
// MessageId: IDSX_IDS_IMAPI_ERASE_DISK
//
// MessageText:
//
//  Erase disk...
//
#define IDSX_IDS_IMAPI_ERASE_DISK        0x40780C17L

// FS CONTROLS Library - YFileTreeCopyDlg
//
// MessageId: IDSX_IDS_YFTDLG_FORMATS
//
// MessageText:
//
//  Folder: \t%A\nFile: \t%N\nSource file: \t%S%P%N\nTarget file: \t%T%P%N\n%F files in %D folders (%B bytes)\nTotal \x25tF files in \x25tD folders (\x25tB bytes)\nFolder: \t%S%P\nOperation: %s\nHardware buffer usage:\nTime: %s total, %s left\n\n
//
#define IDSX_IDS_YFTDLG_FORMATS          0x40780C7FL

//
// MessageId: IDSX_IDS_YFTDLG_COPY
//
// MessageText:
//
//  Prepare copying...\nCopying files...\nDeleting files...\nChecking space...\nErasing...\nBurning...\n\n
//
#define IDSX_IDS_YFTDLG_COPY             0x40780C80L

//
// MessageId: IDSX_IDS_YFTDLG_DELETE
//
// MessageText:
//
//  Prepare deleting...\nCopying files...\nDeleting files...\nVerifying...\n
//
#define IDSX_IDS_YFTDLG_DELETE           0x40780C81L

//
// MessageId: IDSX_IDS_YFTDLG_PROCESS
//
// MessageText:
//
//  Scanning files...\nProcessing files...\nProcessing files...\nVerifying...\n
//
#define IDSX_IDS_YFTDLG_PROCESS          0x40780C82L

//
// MessageId: IDSX_IDS_YFTDLG_IMPORT_FORMATS
//
// MessageText:
//
//  Folder: \t%A\nFile: \t%N\nSource file: \t%S%P%N\nTarget file: \t%a\n%F files in %D folders (%B bytes)\nTotal \x25tF files in \x25tD folders (\x25tB bytes)\nFolder: \t%S%P\n\n
//
#define IDSX_IDS_YFTDLG_IMPORT_FORMATS   0x40780C83L

// SRSFemida - common
//
// MessageId: IDSX_IDS_IMPORT_IMPOSSIBLE
//
// MessageText:
//
//  Import cannot be performed. Last saving was terminated abnormally. 
//
#define IDSX_IDS_IMPORT_IMPOSSIBLE       0x40780C88L

//
// MessageId: IDSX_IDS_QUERY_IMPORT_UPDATE
//
// MessageText:
//
//  Do you want to import document to the primary archive?
//
#define IDSX_IDS_QUERY_IMPORT_UPDATE     0x40780C89L

//
// MessageId: IDSX_IDS_QUERY_IMPORT_OVERWRITE
//
// MessageText:
//
//  Do you want to import document to the primary archive?\nATTENTION! During importing the newer version of document will be deleted!
//
#define IDSX_IDS_QUERY_IMPORT_OVERWRITE  0x40780C8AL

//
// MessageId: IDSX_IDS_RECORD_IMPOSSIBLE
//
// MessageText:
//
//  Record cannot be continued without importing to the primary archive.
//
#define IDSX_IDS_RECORD_IMPOSSIBLE       0x40780C8BL

// SRSFemida - Dialogs - NewCase
//
// MessageId: IDSX_IDCS_ROOM_NUMBER
//
// MessageText:
//
//  Room
//
#define IDSX_IDCS_ROOM_NUMBER            0x40780D00L

//
// MessageId: IDSX_IDCS_MEDIA_SERIAL_NUMBER
//
// MessageText:
//
//  Media serial number (CD/DVD)
//
#define IDSX_IDCS_MEDIA_SERIAL_NUMBER    0x40780D01L

//
// MessageId: IDSX_IDCS_CASE_TYPE
//
// MessageText:
//
//  Type of case
//
#define IDSX_IDCS_CASE_TYPE              0x40780D02L

//
// MessageId: IDSX_IDS_INTERVALS
//
// MessageText:
//
//  any\nhour\nday\nweek\nmonth\n3 months\n1 year\n10 years\n
//
#define IDSX_IDS_INTERVALS               0x40780D03L

//
// MessageId: IDSX_IDS_SEPARATE_WINDOW
//
// MessageText:
//
//  Separate Window
//
#define IDSX_IDS_SEPARATE_WINDOW         0x40780D04L

// 
//
// MessageId: IDSX_IDS_TEMPLATE_NAME_STAGE
//
// MessageText:
//
//  Stage
//
#define IDSX_IDS_TEMPLATE_NAME_STAGE     0x40780FA0L

//
// MessageId: IDSX_IDS_TEMPLATE_NAME_ACTION
//
// MessageText:
//
//  Action
//
#define IDSX_IDS_TEMPLATE_NAME_ACTION    0x40780FA1L

//
// MessageId: IDSX_IDS_TEMPLATE_NAME_PERSON
//
// MessageText:
//
//  Person
//
#define IDSX_IDS_TEMPLATE_NAME_PERSON    0x40780FA2L

//
// MessageId: IDSX_IDS_TEMPLATE_NAME_ACTION_PERSON
//
// MessageText:
//
//  Action + person
//
#define IDSX_IDS_TEMPLATE_NAME_ACTION_PERSON 0x40780FA3L

//
// MessageId: IDSX_IDS_TEMPLATE_NAME_ACTION_PERSON_NOTE
//
// MessageText:
//
//  Action + person + note
//
#define IDSX_IDS_TEMPLATE_NAME_ACTION_PERSON_NOTE 0x40780FA4L

//
// MessageId: IDSX_IDS_TEMPLATE_NAME_ACTION_NOTE
//
// MessageText:
//
//  Action + note
//
#define IDSX_IDS_TEMPLATE_NAME_ACTION_NOTE 0x40780FA5L

//
// MessageId: IDSX_IDS_TEMPLATE_NAME_PERSON_NOTE
//
// MessageText:
//
//  Person + note
//
#define IDSX_IDS_TEMPLATE_NAME_PERSON_NOTE 0x40780FA6L

//
// MessageId: IDSX_IDS_TEMPLATE_NAME_NOTE
//
// MessageText:
//
//  Note
//
#define IDSX_IDS_TEMPLATE_NAME_NOTE      0x40780FA7L

// 
// IDS_ALPHABET=4032
//  VrServer
//
// MessageId: IDSX_IDS_FIND_SERVERS
//
// MessageText:
//
//  Find servers:
//
#define IDSX_IDS_FIND_SERVERS            0x40780FC1L

//
// MessageId: IDSX_IDS_WORD_CLUSTER
//
// MessageText:
//
//  Cluster
//
#define IDSX_IDS_WORD_CLUSTER            0x40780FC2L

//
// MessageId: IDSX_IDS_WORD_SERVER
//
// MessageText:
//
//  Server
//
#define IDSX_IDS_WORD_SERVER             0x40780FC3L

//
// MessageId: IDSX_IDS_WORD_DEVICES
//
// MessageText:
//
//  Devices
//
#define IDSX_IDS_WORD_DEVICES            0x40780FC7L

//
// MessageId: IDSX_IDS_APPLICATION_ALREADY_ACTIVE
//
// MessageText:
//
//  Application already loaded!
//
#define IDSX_IDS_APPLICATION_ALREADY_ACTIVE 0x40780FC4L

//
// MessageId: IDSX_IDS_SECONDS_REMAINED
//
// MessageText:
//
//  %d second(s) remained
//
#define IDSX_IDS_SECONDS_REMAINED        0x40780FC5L

//
// MessageId: IDSX_IDS_INTERNAL_SERVER
//
// MessageText:
//
//  Internal Server
//
#define IDSX_IDS_INTERNAL_SERVER         0x40780FC6L

// IDD_OPEN_PROTOCOL
//
// MessageId: IDSX_IDC_CHECK_NO_VIDEO
//
// MessageText:
//
//  Disable video support
//
#define IDSX_IDC_CHECK_NO_VIDEO          0xC0780643L

//
// MessageId: IDSX_IDC_PRINT_CASE
//
// MessageText:
//
//  Print Case
//
#define IDSX_IDC_PRINT_CASE              0xC0780644L

// 
//
// MessageId: IDSX_ID_CANCEL_EDIT_CNTR
//
// MessageText:
//
//  Cancel edit control\n
//
#define IDSX_ID_CANCEL_EDIT_CNTR         0x40788000L

//
// MessageId: IDSX_ID_CANCEL_EDIT_SRVR
//
// MessageText:
//
//  \n
//
#define IDSX_ID_CANCEL_EDIT_SRVR         0x40788001L

//
// MessageId: IDSX_ID_PROTOCOL_ANSWER
//
// MessageText:
//
//  Question/Answer\nQuestion/Answer
//
#define IDSX_ID_PROTOCOL_ANSWER          0x40788005L

//  SRSFemida - system menu commands   Note: identifier must be even to 16 (ID&0x0F)==0
//
// MessageId: IDSX_ID_SYSMENU_ABOUT
//
// MessageText:
//
//  &About program...
//
#define IDSX_ID_SYSMENU_ABOUT            0x40788010L

//
// MessageId: IDSX_ID_SYSMENU_LANGUAGE
//
// MessageText:
//
//  &Language selection...
//
#define IDSX_ID_SYSMENU_LANGUAGE         0x40788020L

//
// MessageId: IDSX_ID_SYSMENU_OPTIONS
//
// MessageText:
//
//  &Options...
//
#define IDSX_ID_SYSMENU_OPTIONS          0x40788030L

//
// MessageId: IDSX_ID_SYSMENU_TUNE_KEYBOARD
//
// MessageText:
//
//  &Keyboard settings...
//
#define IDSX_ID_SYSMENU_TUNE_KEYBOARD    0x40789850L

//
// MessageId: IDSX_ID_SYSMENU_CHANGE_PARAMETERS
//
// MessageText:
//
//  &Change case number and name
//
#define IDSX_ID_SYSMENU_CHANGE_PARAMETERS 0x40789860L

//
// MessageId: IDSX_ID_SYSMENU_SAVE_AS
//
// MessageText:
//
//  &Save as...
//
#define IDSX_ID_SYSMENU_SAVE_AS          0x40789870L

//
// MessageId: IDSX_ID_SYSMENU_HELP_1
//
// MessageText:
//
//  &Help... 
//
#define IDSX_ID_SYSMENU_HELP_1           0x40789880L

//
// MessageId: IDSX_ID_SYSMENU_HELP_2
//
// MessageText:
//
//  &Help... 
//
#define IDSX_ID_SYSMENU_HELP_2           0x40789890L

//
// MessageId: IDSX_ID_SYSMENU_HELP_3
//
// MessageText:
//
//  &Help... 
//
#define IDSX_ID_SYSMENU_HELP_3           0x407898A0L

//
// MessageId: IDSX_ID_SYSMENU_HELP_4
//
// MessageText:
//
//  &Help... 
//
#define IDSX_ID_SYSMENU_HELP_4           0x407898B0L

//
// MessageId: IDSX_ID_SYSMENU_HELP_5
//
// MessageText:
//
//  &Help... 
//
#define IDSX_ID_SYSMENU_HELP_5           0x407898C0L

//
// MessageId: IDSX_ID_SYSMENU_HELP_6
//
// MessageText:
//
//  &Help... 
//
#define IDSX_ID_SYSMENU_HELP_6           0x407898D0L

//
// MessageId: IDSX_ID_SYSMENU_HELP_7
//
// MessageText:
//
//  &Help... 
//
#define IDSX_ID_SYSMENU_HELP_7           0x407898E0L

//
// MessageId: IDSX_ID_SYSMENU_HELP_8
//
// MessageText:
//
//  &Help... 
//
#define IDSX_ID_SYSMENU_HELP_8           0x407898F0L

//
// MessageId: IDSX_ID_SYSMENU_HELP_9
//
// MessageText:
//
//  &Help... 
//
#define IDSX_ID_SYSMENU_HELP_9           0x40789900L

//
// MessageId: IDSX_ID_SYSMENU_HELP_10
//
// MessageText:
//
//  &Help... 
//
#define IDSX_ID_SYSMENU_HELP_10          0x40789910L

//
// MessageId: IDSX_ID_SYSMENU_HELP_11
//
// MessageText:
//
//  &Help... 
//
#define IDSX_ID_SYSMENU_HELP_11          0x40789920L

//
// MessageId: IDSX_ID_SYSMENU_HELP_12
//
// MessageText:
//
//  &Help... 
//
#define IDSX_ID_SYSMENU_HELP_12          0x40789930L

//
// MessageId: IDSX_ID_SYSMENU_HELP_13
//
// MessageText:
//
//  &Help... 
//
#define IDSX_ID_SYSMENU_HELP_13          0x40789940L

//
// MessageId: IDSX_ID_SYSMENU_HELP_14
//
// MessageText:
//
//  &Help... 
//
#define IDSX_ID_SYSMENU_HELP_14          0x40789950L

//
// MessageId: IDSX_ID_SYSMENU_HELP_15
//
// MessageText:
//
//  &Help... 
//
#define IDSX_ID_SYSMENU_HELP_15          0x40789960L

//
// MessageId: IDSX_ID_SYSMENU_HELP_16
//
// MessageText:
//
//  &Help... 
//
#define IDSX_ID_SYSMENU_HELP_16          0x40789970L

//
// MessageId: IDSX_ID_SYSMENU_MERGE
//
// MessageText:
//
//  &Merge:
//
#define IDSX_ID_SYSMENU_MERGE            0x40789980L

//
// MessageId: IDSX_ID_SYSMENU_IMPORT
//
// MessageText:
//
//  &Import:
//
#define IDSX_ID_SYSMENU_IMPORT           0x40789A50L

//
// MessageId: IDSX_ID_SYSMENU_EXPORT
//
// MessageText:
//
//  &Export:
//
#define IDSX_ID_SYSMENU_EXPORT           0x40789A60L

//
// MessageId: IDSX_ID_SYSMENU_EVENTS
//
// MessageText:
//
//  System E&vent Log:
//
#define IDSX_ID_SYSMENU_EVENTS           0x40789A70L

//   SRS Auto Backup - commands
//
// MessageId: IDSX_ID_RUN
//
// MessageText:
//
//  &Run
//
#define IDSX_ID_RUN                      0x4078991FL

//
// MessageId: IDSX_ID_STOP_STOP
//
// MessageText:
//
//  &Stop
//
#define IDSX_ID_STOP_STOP                0x4078991EL

//
// MessageId: IDSX_ID_EXIT
//
// MessageText:
//
//  &Exit
//
#define IDSX_ID_EXIT                     0x4078991DL

//   SRSFemida - commands
//
// MessageId: IDSX_ID_PLAY
//
// MessageText:
//
//  Play
//
#define IDSX_ID_PLAY                     0x40789921L

//
// MessageId: IDSX_ID_STOP
//
// MessageText:
//
//  Stop
//
#define IDSX_ID_STOP                     0x40789922L

//
// MessageId: IDSX_ID_PAUSE
//
// MessageText:
//
//  Pause
//
#define IDSX_ID_PAUSE                    0x40789923L

//
// MessageId: IDSX_ID_RESUME
//
// MessageText:
//
//  Resume
//
#define IDSX_ID_RESUME                   0x40789924L

//
// MessageId: IDSX_ID_POSITION
//
// MessageText:
//
//  Position
//
#define IDSX_ID_POSITION                 0x40789925L

//
// MessageId: IDSX_ID_AGC
//
// MessageText:
//
//  &Automatic gain control
//
#define IDSX_ID_AGC                      0x40789926L

//
// MessageId: IDSX_ID_ACB
//
// MessageText:
//
//  Automatic channel &balance
//
#define IDSX_ID_ACB                      0x40789927L

//
// MessageId: IDSX_ID_INVERT_CHANNEL
//
// MessageText:
//
//  &Invert channel
//
#define IDSX_ID_INVERT_CHANNEL           0x40789928L

//
// MessageId: IDSX_ID_SELECT_SOUND_DEVICE
//
// MessageText:
//
//  &Select output device...
//
#define IDSX_ID_SELECT_SOUND_DEVICE      0x40789929L

//
// MessageId: IDSX_ID_EQUALIZER
//
// MessageText:
//
//  &Equalizer...
//
#define IDSX_ID_EQUALIZER                0x4078992AL

//
// MessageId: IDSX_ID_AGC_PARAMETERS
//
// MessageText:
//
//  Automatic gain control &parameters...
//
#define IDSX_ID_AGC_PARAMETERS           0x4078992BL

//
// MessageId: IDSX_ID_SUMMARIZE
//
// MessageText:
//
//  &Multiple channels\n&Single channel
//
#define IDSX_ID_SUMMARIZE                0x4078992CL

//
// MessageId: IDSX_ID_ENABLE_DIASABLE
//
// MessageText:
//
//  &Enable\n&Disable
//
#define IDSX_ID_ENABLE_DIASABLE          0x4078992DL

//
// MessageId: IDSX_ID_PEDAL_RIGHT
//
// MessageText:
//
//  Right button of foot pedal
//
#define IDSX_ID_PEDAL_RIGHT              0x4078992EL

//
// MessageId: IDSX_ID_PEDAL_LEFT
//
// MessageText:
//
//  Left button of foot pedal
//
#define IDSX_ID_PEDAL_LEFT               0x4078992FL

// 
//
// MessageId: IDSX_ID_PLAYER_PLAYPAUSE
//
// MessageText:
//
//  Play/Pause
//
#define IDSX_ID_PLAYER_PLAYPAUSE         0x40789931L

//
// MessageId: IDSX_ID_PLAYER_STOP
//
// MessageText:
//
//  Stop
//
#define IDSX_ID_PLAYER_STOP              0x40789932L

//
// MessageId: IDSX_ID_RECORD_START
//
// MessageText:
//
//  Record
//
#define IDSX_ID_RECORD_START             0x40789933L

//
// MessageId: IDSX_ID_RECORD_STOP
//
// MessageText:
//
//  Stop recording
//
#define IDSX_ID_RECORD_STOP              0x40789934L

//
// MessageId: IDSX_ID_PLAYER_NEXT
//
// MessageText:
//
//  Forward
//
#define IDSX_ID_PLAYER_NEXT              0x40789935L

//
// MessageId: IDSX_ID_PLAYER_PRIOR
//
// MessageText:
//
//  Back
//
#define IDSX_ID_PLAYER_PRIOR             0x40789936L

//
// MessageId: IDSX_ID_PLAYER_INCREASE_SCALE
//
// MessageText:
//
//  Zoom in
//
#define IDSX_ID_PLAYER_INCREASE_SCALE    0x40789937L

//
// MessageId: IDSX_ID_PLAYER_DECREASE_SCALE
//
// MessageText:
//
//  Zoom out
//
#define IDSX_ID_PLAYER_DECREASE_SCALE    0x40789938L

//
// MessageId: IDSX_ID_PLAYER_SCROLL_FORWARD
//
// MessageText:
//
//  Scroll forward
//
#define IDSX_ID_PLAYER_SCROLL_FORWARD    0x40789939L

//
// MessageId: IDSX_ID_PLAYER_SCROLL_BACK
//
// MessageText:
//
//  Scroll back
//
#define IDSX_ID_PLAYER_SCROLL_BACK       0x4078993AL

//
// MessageId: IDSX_ID_EXPERT_SETTINGS
//
// MessageText:
//
//  &Advanced settings...
//
#define IDSX_ID_EXPERT_SETTINGS          0x4078993BL

//
// MessageId: IDSX_ID_PROCESSING
//
// MessageText:
//
//  &Sound Processing
//
#define IDSX_ID_PROCESSING               0x4078993CL

// 
//
// MessageId: IDSX_ID_EDITOR_ACTION
//
// MessageText:
//
//  Action
//
#define IDSX_ID_EDITOR_ACTION            0x4078993DL

//
// MessageId: IDSX_ID_EDITOR_PERSONE
//
// MessageText:
//
//  Participant
//
#define IDSX_ID_EDITOR_PERSONE           0x4078993EL

//
// MessageId: IDSX_ID_EDITOR_LOCATION
//
// MessageText:
//
//  Location
//
#define IDSX_ID_EDITOR_LOCATION          0x4078993FL

//
// MessageId: IDSX_ID_EDITOR_LOCATION1
//
// MessageText:
//
//  Location 1
//
#define IDSX_ID_EDITOR_LOCATION1         0x40789941L

//
// MessageId: IDSX_ID_EDITOR_LOCATION2
//
// MessageText:
//
//  Location 2
//
#define IDSX_ID_EDITOR_LOCATION2         0x40789942L

//
// MessageId: IDSX_ID_EDITOR_LOCATION3
//
// MessageText:
//
//  Location 3
//
#define IDSX_ID_EDITOR_LOCATION3         0x40789943L

//
// MessageId: IDSX_ID_EDITOR_LOCATION4
//
// MessageText:
//
//  Location 4
//
#define IDSX_ID_EDITOR_LOCATION4         0x40789944L

//
// MessageId: IDSX_ID_EDITOR_LOCATION5
//
// MessageText:
//
//  Location 5
//
#define IDSX_ID_EDITOR_LOCATION5         0x40789945L

//
// MessageId: IDSX_ID_EDITOR_LOCATION6
//
// MessageText:
//
//  Location 6
//
#define IDSX_ID_EDITOR_LOCATION6         0x40789946L

//
// MessageId: IDSX_ID_EDITOR_LOCATION7
//
// MessageText:
//
//  Location 7
//
#define IDSX_ID_EDITOR_LOCATION7         0x40789947L

//
// MessageId: IDSX_ID_EDITOR_LOCATION8
//
// MessageText:
//
//  Location 8
//
#define IDSX_ID_EDITOR_LOCATION8         0x40789948L

//
// MessageId: IDSX_ID_EDITOR_LOCATION9
//
// MessageText:
//
//  Location 9
//
#define IDSX_ID_EDITOR_LOCATION9         0x40789949L

//
// MessageId: IDSX_ID_PLAYER_LOCATION
//
// MessageText:
//
//  Listen location
//
#define IDSX_ID_PLAYER_LOCATION          0x4078994AL

//
// MessageId: IDSX_ID_EDITOR_EVENT
//
// MessageText:
//
//  New event
//
#define IDSX_ID_EDITOR_EVENT             0x4078994BL

//
// MessageId: IDSX_ID_RESET_VOLUMES
//
// MessageText:
//
//  &Reset Volumes
//
#define IDSX_ID_RESET_VOLUMES            0x40789984L

//
// MessageId: IDSX_ID_SEARCH
//
// MessageText:
//
//  &Search:
//
#define IDSX_ID_SEARCH                   0x40789990L

//
// MessageId: IDSX_ID_SEARCH_AND_REPLACE
//
// MessageText:
//
//  &Replace:
//
#define IDSX_ID_SEARCH_AND_REPLACE       0x40789991L

//
// MessageId: IDSX_ID_PEDAL_MIDDLE
//
// MessageText:
//
//  Middle button of foot pedal
//
#define IDSX_ID_PEDAL_MIDDLE             0x40789992L

//
// MessageId: IDSX_ID_REPORT_APPOINT
//
// MessageText:
//
//  Assign transcription task
//
#define IDSX_ID_REPORT_APPOINT           0x40789993L

//
// MessageId: IDSX_ID_REPORT_UPDATE
//
// MessageText:
//
//  Update transcriptions
//
#define IDSX_ID_REPORT_UPDATE            0x40789994L

//   SRSFemida - IDD_VR_COURT
//
// MessageId: IDSX_IDC_STATIC_REPLACE_MESSAGE_A
//
// MessageText:
//
//  Current document template is not present on disk. Do you want to save template on disk?\nSave template on disk.\nReplace document template without saving (current document template will be deleted completely!)\n
//
#define IDSX_IDC_STATIC_REPLACE_MESSAGE_A 0x407899A0L

//
// MessageId: IDSX_IDC_STATIC_REPLACE_MESSAGE_B
//
// MessageText:
//
//  
//
#define IDSX_IDC_STATIC_REPLACE_MESSAGE_B 0x407899A1L

//
// MessageId: IDSX_IDC_STATIC_REPLACE_MESSAGE_C
//
// MessageText:
//
//  
//
#define IDSX_IDC_STATIC_REPLACE_MESSAGE_C 0x407899A2L

//
// MessageId: IDSX_IDC_STATIC_REPLACE_MESSAGE_D
//
// MessageText:
//
//  Current document template and template on disk mismatch. Do you want to save template on disk?\nSave current document template with other name.\nReplace document template without saving (current document template will be deleted completely!)\n
//
#define IDSX_IDC_STATIC_REPLACE_MESSAGE_D 0x407899A3L

//   SRSFemida - errors
//
// MessageId: IDSX_ERR_FAILURE
//
// MessageText:
//
//  Unknown error
//
#define IDSX_ERR_FAILURE                 0x40789C40L

//
// MessageId: IDSX_ERR_RECORD_NOT_FOUND
//
// MessageText:
//
//  There's no record
//
#define IDSX_ERR_RECORD_NOT_FOUND        0x40789D08L

//
// MessageId: IDSX_ERR_BAD_TEMPLATE
//
// MessageText:
//
//  Wrong format of template
//
#define IDSX_ERR_BAD_TEMPLATE            0x40789D09L

//
// MessageId: IDSX_ERR_TEMPLATES_NOT_FOUND
//
// MessageText:
//
//  Templates of trials are not found
//
#define IDSX_ERR_TEMPLATES_NOT_FOUND     0x40789D0AL

//
// MessageId: IDSX_ERR_TEMPLATE_NAME_ALREDY_EXIST
//
// MessageText:
//
//  Such name was already used
//
#define IDSX_ERR_TEMPLATE_NAME_ALREDY_EXIST 0x40789D0BL

//
// MessageId: IDSX_ERR_NAME_NOT_DEFINED
//
// MessageText:
//
//  Surname is not given
//
#define IDSX_ERR_NAME_NOT_DEFINED        0x40789D0CL

//
// MessageId: IDSX_ERR_PERSONE_ALREADY_DEFINED
//
// MessageText:
//
//  Such person already exists
//
#define IDSX_ERR_PERSONE_ALREADY_DEFINED 0x40789D0DL

//
// MessageId: IDSX_ERR_BAD_HEADER_FORMAT
//
// MessageText:
//
//  Wrong format of record of template of title
//
#define IDSX_ERR_BAD_HEADER_FORMAT       0x40789D0EL

//
// MessageId: IDSX_ERR_BAD_DATE
//
// MessageText:
//
//  Wrong date
//
#define IDSX_ERR_BAD_DATE                0x40789D0FL

//
// MessageId: IDSX_ERR_BAD_BUSINESS_NUMBER
//
// MessageText:
//
//  Wrong case number - \nThe case number cannot be blank and\n include symbols / : > < = \? \" \\ |
//
#define IDSX_ERR_BAD_BUSINESS_NUMBER     0x40789D10L

//
// MessageId: IDSX_ERR_TEMPLATE_NOT_FOUND
//
// MessageText:
//
//  Template is not found
//
#define IDSX_ERR_TEMPLATE_NOT_FOUND      0x40789D11L

//
// MessageId: IDSX_ERR_NOT_SAVED
//
// MessageText:
//
//  Changes you made are not saved. Do you want to save them?\n\"Yes\" - changes will be saved\n\"No\" - changes will be lost \n\"Cancel\" - close this dialog window and return to the main window.
//
#define IDSX_ERR_NOT_SAVED               0x40789D12L

//
// MessageId: IDSX_ERR_PHONO_BOUNDARIES
//
// MessageText:
//
//  Start and end points of sound track cannot be defined. \nThe sound track cannot be empty and has to be marked with <<<end>>>  or <<<break>>> at the end.
//
#define IDSX_ERR_PHONO_BOUNDARIES        0x40789D13L

//
// MessageId: IDSX_ERR_OUT_OF_DISK_SPACE
//
// MessageText:
//
//  Not enough free space on disk.\nPlease insert an empty disk \n to burn it. 
//
#define IDSX_ERR_OUT_OF_DISK_SPACE       0x40789D14L

//
// MessageId: IDSX_ERR_PROTOCOL_IS_NOT_FORMED
//
// MessageText:
//
//  Please enter any action!
//
#define IDSX_ERR_PROTOCOL_IS_NOT_FORMED  0x40789D15L

//
// MessageId: IDSX_ERR_CHANGE_RECORDING_SETTINGS_IMPOSSIBLE
//
// MessageText:
//
//  You cannot change record options while recording! 
//
#define IDSX_ERR_CHANGE_RECORDING_SETTINGS_IMPOSSIBLE 0x40789D16L

//
// MessageId: IDSX_ERR_CAN_NOT_CREATE_DIRECTORY
//
// MessageText:
//
//  The file cannot be created \n\"%s\"
//
#define IDSX_ERR_CAN_NOT_CREATE_DIRECTORY 0x40789D17L

//
// MessageId: IDSX_ERR_BACKUP_PRESENT
//
// MessageText:
//
//  Last saving was terminated abnormally.\nWould you like to restore data from backup?
//
#define IDSX_ERR_BACKUP_PRESENT          0x40789D18L

//
// MessageId: IDSX_ERR_DLL_SAVE_TO_ANOTHER
//
// MessageText:
//
//  Saving was terminated.\nDo you want to save to another directory?
//
#define IDSX_ERR_DLL_SAVE_TO_ANOTHER     0x40789D19L

//
// MessageId: IDSX_ERR_CHANNELS_IS_NOT_SELECTED
//
// MessageText:
//
//  Please select channels! 
//
#define IDSX_ERR_CHANNELS_IS_NOT_SELECTED 0x40789D1AL

//
// MessageId: IDSX_ERR_BAD_RECORD_FORMAT
//
// MessageText:
//
//  Unknown format of record!
//
#define IDSX_ERR_BAD_RECORD_FORMAT       0x40789D1BL

//
// MessageId: IDSX_ERR_ROLE_NOT_DEFINED
//
// MessageText:
//
//  Role is not specified.
//
#define IDSX_ERR_ROLE_NOT_DEFINED        0x40789D1CL

//
// MessageId: IDSX_ERR_DISK_NOT_FORMATTED
//
// MessageText:
//
//  Disk is not formatted
//
#define IDSX_ERR_DISK_NOT_FORMATTED      0x40789D1EL

//
// MessageId: IDSX_ERR_AUDIO_OUTPUT_DEVICE_NOT_FOUND
//
// MessageText:
//
//  Audio output device is not found
//
#define IDSX_ERR_AUDIO_OUTPUT_DEVICE_NOT_FOUND 0x40789D1FL

//
// MessageId: IDSX_ERR_REPLICATION_FAILED
//
// MessageText:
//
//  Replication failed
//
#define IDSX_ERR_REPLICATION_FAILED      0x40789D20L

//
// MessageId: IDSX_ERR_SELECTION_NOT_DEFINED
//
// MessageText:
//
//  Selection is not defined
//
#define IDSX_ERR_SELECTION_NOT_DEFINED   0x40789D21L

//
// MessageId: IDSX_ERR_SERVER_NOT_DEFINED
//
// MessageText:
//
//  Server is not specified. Continue by default?
//
#define IDSX_ERR_SERVER_NOT_DEFINED      0x40789D22L

//
// MessageId: IDSX_IDS_NETWORK_ALSO
//
// MessageText:
//
//  save to network archive also
//
#define IDSX_IDS_NETWORK_ALSO            0x40789D23L

//
// MessageId: IDSX_ERR_IMAPI_FORMAT2_DATA_MEDIA_STATE
//
// MessageText:
//
//  overwrite only\nrandomly writable\nblank\nappendable\nfninal session\ndamaged\nerase required\nnon empty session\nwrite protected\nfinalized\nunsupported media
//
#define IDSX_ERR_IMAPI_FORMAT2_DATA_MEDIA_STATE 0x40789D24L

// 
//
// MessageId: IDSX_ERR_next
//
// MessageText:
//
//  next
//
#define IDSX_ERR_next                    0x40789D25L

// SRSFemida - license
// AFX_IDS_APP_TITLE = 57344 - application individual
//
// MessageId: IDSX_IDS_APP_LICENSE
//
// MessageText:
//
//  User:%s\r\nOrganization:%s\r\nSerial number:%s
//
#define IDSX_IDS_APP_LICENSE             0x4078E010L

//
// MessageId: IDSX_IDS_APP_LICENSE_LOCALIZED
//
// MessageText:
//
//  
//
#define IDSX_IDS_APP_LICENSE_LOCALIZED   0x4078E011L

// MFC resource strings
//
// MessageId: IDSX_ID_FILE_NEW
//
// MessageText:
//
//  Create a new document\nNew
//
#define IDSX_ID_FILE_NEW                 0x4078E100L

//
// MessageId: IDSX_ID_FILE_OPEN
//
// MessageText:
//
//  Open an existing document\nOpen
//
#define IDSX_ID_FILE_OPEN                0x4078E101L

//
// MessageId: IDSX_ID_FILE_CLOSE
//
// MessageText:
//
//  Close the active document\nClose
//
#define IDSX_ID_FILE_CLOSE               0x4078E102L

//
// MessageId: IDSX_ID_FILE_SAVE
//
// MessageText:
//
//  Save the active document\nSave
//
#define IDSX_ID_FILE_SAVE                0x4078E103L

//
// MessageId: IDSX_ID_FILE_SAVE_AS
//
// MessageText:
//
//  Save the active document with a new name\nSave As
//
#define IDSX_ID_FILE_SAVE_AS             0x4078E104L

//
// MessageId: IDSX_ID_FILE_PAGE_SETUP
//
// MessageText:
//
//  Change the printing options\nPage Setup
//
#define IDSX_ID_FILE_PAGE_SETUP          0x4078E105L

//
// MessageId: IDSX_ID_FILE_PRINT_SETUP
//
// MessageText:
//
//  Change the printer and printing options\nPrint Setup
//
#define IDSX_ID_FILE_PRINT_SETUP         0x4078E106L

//
// MessageId: IDSX_ID_FILE_PRINT
//
// MessageText:
//
//  Print the active document\nPrint
//
#define IDSX_ID_FILE_PRINT               0x4078E107L

//
// MessageId: IDSX_ID_FILE_PRINT_DIRECT
//
// MessageText:
//
//  ?
//
#define IDSX_ID_FILE_PRINT_DIRECT        0x4078E108L

//
// MessageId: IDSX_ID_FILE_PRINT_PREVIEW
//
// MessageText:
//
//  Display full pages\nPrint Preview
//
#define IDSX_ID_FILE_PRINT_PREVIEW       0x4078E109L

//
// MessageId: IDSX_ID_FILE_UPDATE
//
// MessageText:
//
//  Update the container to show any changes\nUpdate
//
#define IDSX_ID_FILE_UPDATE              0x4078E10AL

//
// MessageId: IDSX_ID_FILE_SAVE_COPY_AS
//
// MessageText:
//
//  Save a copy of the active document with a new name\nSave Copy
//
#define IDSX_ID_FILE_SAVE_COPY_AS        0x4078E10BL

//
// MessageId: IDSX_ID_FILE_SEND_MAIL
//
// MessageText:
//
//  Send the active document through electronic mail\nSend Mail
//
#define IDSX_ID_FILE_SEND_MAIL           0x4078E10CL

//
// MessageId: IDSX_ID_FILE_NEW_FRAME
//
// MessageText:
//
//  ?
//
#define IDSX_ID_FILE_NEW_FRAME           0x4078E10DL

//
// MessageId: IDSX_ID_FILE_MRU_FILE1
//
// MessageText:
//
//  Open this document
//
#define IDSX_ID_FILE_MRU_FILE1           0x4078E110L

//
// MessageId: IDSX_ID_FILE_MRU_FILE2
//
// MessageText:
//
//  Open this document
//
#define IDSX_ID_FILE_MRU_FILE2           0x4078E111L

//
// MessageId: IDSX_ID_FILE_MRU_FILE3
//
// MessageText:
//
//  Open this document
//
#define IDSX_ID_FILE_MRU_FILE3           0x4078E112L

//
// MessageId: IDSX_ID_FILE_MRU_FILE4
//
// MessageText:
//
//  Open this document
//
#define IDSX_ID_FILE_MRU_FILE4           0x4078E113L

//
// MessageId: IDSX_ID_FILE_MRU_FILE5
//
// MessageText:
//
//  Open this document
//
#define IDSX_ID_FILE_MRU_FILE5           0x4078E114L

//
// MessageId: IDSX_ID_FILE_MRU_FILE6
//
// MessageText:
//
//  Open this document
//
#define IDSX_ID_FILE_MRU_FILE6           0x4078E115L

//
// MessageId: IDSX_ID_FILE_MRU_FILE7
//
// MessageText:
//
//  Open this document
//
#define IDSX_ID_FILE_MRU_FILE7           0x4078E116L

//
// MessageId: IDSX_ID_FILE_MRU_FILE8
//
// MessageText:
//
//  Open this document
//
#define IDSX_ID_FILE_MRU_FILE8           0x4078E117L

//
// MessageId: IDSX_ID_FILE_MRU_FILE9
//
// MessageText:
//
//  Open this document
//
#define IDSX_ID_FILE_MRU_FILE9           0x4078E118L

//
// MessageId: IDSX_ID_FILE_MRU_FILE10
//
// MessageText:
//
//  Open this document
//
#define IDSX_ID_FILE_MRU_FILE10          0x4078E119L

//
// MessageId: IDSX_ID_FILE_MRU_FILE11
//
// MessageText:
//
//  Open this document
//
#define IDSX_ID_FILE_MRU_FILE11          0x4078E11AL

//
// MessageId: IDSX_ID_FILE_MRU_FILE12
//
// MessageText:
//
//  Open this document
//
#define IDSX_ID_FILE_MRU_FILE12          0x4078E11BL

//
// MessageId: IDSX_ID_FILE_MRU_FILE13
//
// MessageText:
//
//  Open this document
//
#define IDSX_ID_FILE_MRU_FILE13          0x4078E11CL

//
// MessageId: IDSX_ID_FILE_MRU_FILE14
//
// MessageText:
//
//  Open this document
//
#define IDSX_ID_FILE_MRU_FILE14          0x4078E11DL

//
// MessageId: IDSX_ID_FILE_MRU_FILE15
//
// MessageText:
//
//  Open this document
//
#define IDSX_ID_FILE_MRU_FILE15          0x4078E11EL

//
// MessageId: IDSX_ID_FILE_MRU_FILE16
//
// MessageText:
//
//  Open this document
//
#define IDSX_ID_FILE_MRU_FILE16          0x4078E11FL

//
// MessageId: IDSX_ID_EDIT_CLEAR
//
// MessageText:
//
//  Erase the selection\nErase
//
#define IDSX_ID_EDIT_CLEAR               0x4078E120L

//
// MessageId: IDSX_ID_EDIT_CLEAR_ALL
//
// MessageText:
//
//  Erase everything\nErase All
//
#define IDSX_ID_EDIT_CLEAR_ALL           0x4078E121L

//
// MessageId: IDSX_ID_EDIT_COPY
//
// MessageText:
//
//  Copy the selection and put it on the Clipboard\nCopy
//
#define IDSX_ID_EDIT_COPY                0x4078E122L

//
// MessageId: IDSX_ID_EDIT_CUT
//
// MessageText:
//
//  Cut the selection and put it on the Clipboard\nCut
//
#define IDSX_ID_EDIT_CUT                 0x4078E123L

//
// MessageId: IDSX_ID_EDIT_FIND
//
// MessageText:
//
//  Find the specified text\nFind
//
#define IDSX_ID_EDIT_FIND                0x4078E124L

//
// MessageId: IDSX_ID_EDIT_PASTE
//
// MessageText:
//
//  Insert Clipboard contents\nPaste
//
#define IDSX_ID_EDIT_PASTE               0x4078E125L

//
// MessageId: IDSX_ID_EDIT_PASTE_LINK
//
// MessageText:
//
//  Insert Clipboard contents and a link to its source\nPaste Link
//
#define IDSX_ID_EDIT_PASTE_LINK          0x4078E126L

//
// MessageId: IDSX_ID_EDIT_PASTE_SPECIAL
//
// MessageText:
//
//  Insert Clipboard contents with options\nPaste Special
//
#define IDSX_ID_EDIT_PASTE_SPECIAL       0x4078E127L

//
// MessageId: IDSX_ID_EDIT_REPEAT
//
// MessageText:
//
//  Repeat the last action\nRepeat
//
#define IDSX_ID_EDIT_REPEAT              0x4078E128L

//
// MessageId: IDSX_ID_EDIT_REPLACE
//
// MessageText:
//
//  Replace specific text with different text\nReplace
//
#define IDSX_ID_EDIT_REPLACE             0x4078E129L

//
// MessageId: IDSX_ID_EDIT_SELECT_ALL
//
// MessageText:
//
//  Select the entire document\nSelect All
//
#define IDSX_ID_EDIT_SELECT_ALL          0x4078E12AL

//
// MessageId: IDSX_ID_EDIT_UNDO
//
// MessageText:
//
//  Undo the last action\nUndo
//
#define IDSX_ID_EDIT_UNDO                0x4078E12BL

//
// MessageId: IDSX_ID_EDIT_REDO
//
// MessageText:
//
//  Redo the previously undone action\nRedo
//
#define IDSX_ID_EDIT_REDO                0x4078E12CL

//
// MessageId: IDSX_ID_WINDOW_NEW
//
// MessageText:
//
//  Open another window for the active document\nNew Window
//
#define IDSX_ID_WINDOW_NEW               0x4078E130L

//
// MessageId: IDSX_ID_WINDOW_ARRANGE
//
// MessageText:
//
//  Arrange icons at the bottom of the window\nArrange Icons
//
#define IDSX_ID_WINDOW_ARRANGE           0x4078E131L

//
// MessageId: IDSX_ID_WINDOW_CASCADE
//
// MessageText:
//
//  Arrange windows so they overlap\nCascade Windows
//
#define IDSX_ID_WINDOW_CASCADE           0x4078E132L

//
// MessageId: IDSX_ID_WINDOW_TILE_HORZ
//
// MessageText:
//
//  Arrange windows as non-overlapping tiles\nTile Windows
//
#define IDSX_ID_WINDOW_TILE_HORZ         0x4078E133L

//
// MessageId: IDSX_ID_WINDOW_TILE_VERT
//
// MessageText:
//
//  Arrange windows as non-overlapping tiles\nTile Windows
//
#define IDSX_ID_WINDOW_TILE_VERT         0x4078E134L

//
// MessageId: IDSX_ID_WINDOW_SPLIT
//
// MessageText:
//
//  Split the active window into panes\nSplit
//
#define IDSX_ID_WINDOW_SPLIT             0x4078E135L

//
// MessageId: IDSX_ID_APP_ABOUT
//
// MessageText:
//
//  Display program information, version number and copyright\nAbout
//
#define IDSX_ID_APP_ABOUT                0x4078E140L

//
// MessageId: IDSX_ID_APP_EXIT
//
// MessageText:
//
//  Quit the application; prompts to save documents\nExit
//
#define IDSX_ID_APP_EXIT                 0x4078E141L

//
// MessageId: IDSX_ID_HELP_INDEX
//
// MessageText:
//
//  List Help topics\nHelp Index
//
#define IDSX_ID_HELP_INDEX               0x4078E142L

//
// MessageId: IDSX_ID_HELP_FINDER
//
// MessageText:
//
//  List Help topics\nHelp Topics
//
#define IDSX_ID_HELP_FINDER              0x4078E143L

//
// MessageId: IDSX_ID_HELP_USING
//
// MessageText:
//
//  Display instructions about how to use help\nHelp
//
#define IDSX_ID_HELP_USING               0x4078E144L

//
// MessageId: IDSX_ID_CONTEXT_HELP
//
// MessageText:
//
//  Display help for clicked on buttons, menus and windows\nHelp
//
#define IDSX_ID_CONTEXT_HELP             0x4078E145L

//
// MessageId: IDSX_ID_HELP
//
// MessageText:
//
//  Display help for current task or command\nHelp
//
#define IDSX_ID_HELP                     0x4078E146L

//
// MessageId: IDSX_ID_DEFAULT_HELP
//
// MessageText:
//
//  ?
//
#define IDSX_ID_DEFAULT_HELP             0x4078E147L

//
// MessageId: IDSX_ID_NEXT_PANE
//
// MessageText:
//
//  Switch to the next window pane\nNext Pane
//
#define IDSX_ID_NEXT_PANE                0x4078E150L

//
// MessageId: IDSX_ID_PREV_PANE
//
// MessageText:
//
//  Switch back to the previous window pane\nPrevious Pane
//
#define IDSX_ID_PREV_PANE                0x4078E151L

//
// MessageId: IDSX_ID_FORMAT_FONT
//
// MessageText:
//
//  Select font for current selection\nFont
//
#define IDSX_ID_FORMAT_FONT              0x4078E160L

//
// MessageId: IDSX_ID_OLE_INSERT_NEW
//
// MessageText:
//
//  Insert new embedded object\nNew Object
//
#define IDSX_ID_OLE_INSERT_NEW           0x4078E200L

//
// MessageId: IDSX_ID_OLE_EDIT_LINKS
//
// MessageText:
//
//  Edit linked objects\nEdit Links
//
#define IDSX_ID_OLE_EDIT_LINKS           0x4078E201L

//
// MessageId: IDSX_ID_OLE_EDIT_CONVERT
//
// MessageText:
//
//  Convert selected object between types\nConvert Object
//
#define IDSX_ID_OLE_EDIT_CONVERT         0x4078E202L

//
// MessageId: IDSX_ID_OLE_EDIT_CHANGE_ICON
//
// MessageText:
//
//  Change icon of selected object\nChange Icon
//
#define IDSX_ID_OLE_EDIT_CHANGE_ICON     0x4078E203L

//
// MessageId: IDSX_ID_OLE_EDIT_PROPERTIES
//
// MessageText:
//
//  ?
//
#define IDSX_ID_OLE_EDIT_PROPERTIES      0x4078E204L

//
// MessageId: IDSX_ID_OLE_VERB_FIRST
//
// MessageText:
//
//  Activate embedded or linked object
//
#define IDSX_ID_OLE_VERB_FIRST           0x4078E210L

//
// MessageId: IDSX_ID_OLE_VERB_LAST
//
// MessageText:
//
//  Activate embedded or linked object
//
#define IDSX_ID_OLE_VERB_LAST            0x4078E21FL

//
// MessageId: IDSX_AFX_ID_PREVIEW_CLOSE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_ID_PREVIEW_CLOSE        0x4078E230L

//
// MessageId: IDSX_AFX_ID_PREVIEW_NUMPAGE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_ID_PREVIEW_NUMPAGE      0x4078E231L

//
// MessageId: IDSX_AFX_ID_PREVIEW_NEXT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_ID_PREVIEW_NEXT         0x4078E232L

//
// MessageId: IDSX_AFX_ID_PREVIEW_PREV
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_ID_PREVIEW_PREV         0x4078E233L

//
// MessageId: IDSX_AFX_ID_PREVIEW_PRINT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_ID_PREVIEW_PRINT        0x4078E234L

//
// MessageId: IDSX_AFX_ID_PREVIEW_ZOOMIN
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_ID_PREVIEW_ZOOMIN       0x4078E235L

//
// MessageId: IDSX_AFX_ID_PREVIEW_ZOOMOUT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_ID_PREVIEW_ZOOMOUT      0x4078E236L

//
// MessageId: IDSX_ID_INDICATOR_EXT
//
// MessageText:
//
//  EXT
//
#define IDSX_ID_INDICATOR_EXT            0x4078E700L

//
// MessageId: IDSX_ID_INDICATOR_CAPS
//
// MessageText:
//
//  CAP
//
#define IDSX_ID_INDICATOR_CAPS           0x4078E701L

//
// MessageId: IDSX_ID_INDICATOR_NUM
//
// MessageText:
//
//  NUM
//
#define IDSX_ID_INDICATOR_NUM            0x4078E702L

//
// MessageId: IDSX_ID_INDICATOR_SCRL
//
// MessageText:
//
//  SCRL
//
#define IDSX_ID_INDICATOR_SCRL           0x4078E703L

//
// MessageId: IDSX_ID_INDICATOR_OVR
//
// MessageText:
//
//  OVR
//
#define IDSX_ID_INDICATOR_OVR            0x4078E704L

//
// MessageId: IDSX_ID_INDICATOR_REC
//
// MessageText:
//
//  REC
//
#define IDSX_ID_INDICATOR_REC            0x4078E705L

//
// MessageId: IDSX_ID_VIEW_TOOLBAR
//
// MessageText:
//
//  Show or hide the toolbar\nToggle ToolBar
//
#define IDSX_ID_VIEW_TOOLBAR             0x4078E800L

//
// MessageId: IDSX_ID_VIEW_STATUS_BAR
//
// MessageText:
//
//  Show or hide the status bar\nToggle StatusBar
//
#define IDSX_ID_VIEW_STATUS_BAR          0x4078E801L

//
// MessageId: IDSX_ID_VIEW_REBAR
//
// MessageText:
//
//  ?
//
#define IDSX_ID_VIEW_REBAR               0x4078E804L

//
// MessageId: IDSX_ID_VIEW_AUTOARRANGE
//
// MessageText:
//
//  Arrange icons on a grid.
//
#define IDSX_ID_VIEW_AUTOARRANGE         0x4078E805L

//
// MessageId: IDSX_ID_VIEW_SMALLICON
//
// MessageText:
//
//  Display items by using small icons.\nSmall Icons
//
#define IDSX_ID_VIEW_SMALLICON           0x4078E810L

//
// MessageId: IDSX_ID_VIEW_LARGEICON
//
// MessageText:
//
//  Display items by using large icons.\nLarge Icons
//
#define IDSX_ID_VIEW_LARGEICON           0x4078E811L

//
// MessageId: IDSX_ID_VIEW_LIST
//
// MessageText:
//
//  Displays items in a list.\nList
//
#define IDSX_ID_VIEW_LIST                0x4078E812L

//
// MessageId: IDSX_ID_VIEW_DETAILS
//
// MessageText:
//
//  Displays detailed information about each item in the window.\nDetails
//
#define IDSX_ID_VIEW_DETAILS             0x4078E813L

//
// MessageId: IDSX_ID_VIEW_LINEUP
//
// MessageText:
//
//  Arranges icons in a grid.
//
#define IDSX_ID_VIEW_LINEUP              0x4078E814L

//
// MessageId: IDSX_ID_VIEW_BYNAME
//
// MessageText:
//
//  Sorts the icons alphabetically.
//
#define IDSX_ID_VIEW_BYNAME              0x4078E815L

//
// MessageId: IDSX_ID_RECORD_FIRST
//
// MessageText:
//
//  Move to first record\nFirst Record
//
#define IDSX_ID_RECORD_FIRST             0x4078E900L

//
// MessageId: IDSX_ID_RECORD_LAST
//
// MessageText:
//
//  Move to final record\nLast Record
//
#define IDSX_ID_RECORD_LAST              0x4078E901L

//
// MessageId: IDSX_ID_RECORD_NEXT
//
// MessageText:
//
//  Move to next record\nNext Record
//
#define IDSX_ID_RECORD_NEXT              0x4078E902L

//
// MessageId: IDSX_ID_RECORD_PREV
//
// MessageText:
//
//  Move to previous record\nPrevious Record
//
#define IDSX_ID_RECORD_PREV              0x4078E903L

//
// MessageId: IDSX_AFX_IDS_SCSIZE
//
// MessageText:
//
//  Change the window size
//
#define IDSX_AFX_IDS_SCSIZE              0x4078EF00L

//
// MessageId: IDSX_AFX_IDS_SCMOVE
//
// MessageText:
//
//  Change the window position
//
#define IDSX_AFX_IDS_SCMOVE              0x4078EF01L

//
// MessageId: IDSX_AFX_IDS_SCMINIMIZE
//
// MessageText:
//
//  Reduce the window to an icon
//
#define IDSX_AFX_IDS_SCMINIMIZE          0x4078EF02L

//
// MessageId: IDSX_AFX_IDS_SCMAXIMIZE
//
// MessageText:
//
//  Enlarge the window to full size
//
#define IDSX_AFX_IDS_SCMAXIMIZE          0x4078EF03L

//
// MessageId: IDSX_AFX_IDS_SCNEXTWINDOW
//
// MessageText:
//
//  Switch to the next document window
//
#define IDSX_AFX_IDS_SCNEXTWINDOW        0x4078EF04L

//
// MessageId: IDSX_AFX_IDS_SCPREVWINDOW
//
// MessageText:
//
//  Switch to the previous document window
//
#define IDSX_AFX_IDS_SCPREVWINDOW        0x4078EF05L

//
// MessageId: IDSX_AFX_IDS_SCCLOSE
//
// MessageText:
//
//  Close the active window and prompts to save the documents
//
#define IDSX_AFX_IDS_SCCLOSE             0x4078EF06L

//
// MessageId: IDSX_AFX_IDS_SCRESTORE
//
// MessageText:
//
//  Restore the window to normal size
//
#define IDSX_AFX_IDS_SCRESTORE           0x4078EF12L

//
// MessageId: IDSX_AFX_IDS_SCTASKLIST
//
// MessageText:
//
//  Activate Task List
//
#define IDSX_AFX_IDS_SCTASKLIST          0x4078EF13L

//  AFX_IDS_MDICHILD = 61215 = 0xEF1F
//
// MessageId: IDSX_AFX_IDS_DESKACCESSORY
//
// MessageText:
//
//  Open the selected item
//
#define IDSX_AFX_IDS_DESKACCESSORY       0x4078EFDAL

// 
//
// MessageId: IDSX_AFX_IDS_OPENFILE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_OPENFILE            0x4078F000L

//
// MessageId: IDSX_AFX_IDS_SAVEFILE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_SAVEFILE            0x4078F001L

//
// MessageId: IDSX_AFX_IDS_ALLFILTER
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_ALLFILTER           0x4078F002L

//
// MessageId: IDSX_AFX_IDS_UNTITLED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_UNTITLED            0x4078F003L

//
// MessageId: IDSX_AFX_IDS_SAVEFILECOPY
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_SAVEFILECOPY        0x4078F004L

//
// MessageId: IDSX_AFX_IDS_PREVIEW_CLOSE
//
// MessageText:
//
//  Close print preview mode\nCancel Preview
//
#define IDSX_AFX_IDS_PREVIEW_CLOSE       0x4078F005L

//
// MessageId: IDSX_AFX_IDS_UNNAMED_FILE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_UNNAMED_FILE        0x4078F006L

//
// MessageId: IDSX_AFX_IDS_HIDE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_HIDE                0x4078F011L

//
// MessageId: IDSX_AFX_IDP_NO_ERROR_AVAILABLE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_NO_ERROR_AVAILABLE  0x4078F020L

//
// MessageId: IDSX_AFX_IDS_NOT_SUPPORTED_EXCEPTION
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_NOT_SUPPORTED_EXCEPTION 0x4078F021L

//
// MessageId: IDSX_AFX_IDS_RESOURCE_EXCEPTION
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_RESOURCE_EXCEPTION  0x4078F022L

//
// MessageId: IDSX_AFX_IDS_MEMORY_EXCEPTION
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_MEMORY_EXCEPTION    0x4078F023L

//
// MessageId: IDSX_AFX_IDS_USER_EXCEPTION
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_USER_EXCEPTION      0x4078F024L

//
// MessageId: IDSX_AFX_IDS_INVALID_ARG_EXCEPTION
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_INVALID_ARG_EXCEPTION 0x4078F025L

//
// MessageId: IDSX_AFX_IDS_PRINTONPORT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_PRINTONPORT         0x4078F040L

//
// MessageId: IDSX_AFX_IDS_ONEPAGE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_ONEPAGE             0x4078F041L

//
// MessageId: IDSX_AFX_IDS_TWOPAGE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_TWOPAGE             0x4078F042L

//
// MessageId: IDSX_AFX_IDS_PRINTPAGENUM
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_PRINTPAGENUM        0x4078F043L

//
// MessageId: IDSX_AFX_IDS_PREVIEWPAGEDESC
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_PREVIEWPAGEDESC     0x4078F044L

//
// MessageId: IDSX_AFX_IDS_PRINTDEFAULTEXT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_PRINTDEFAULTEXT     0x4078F045L

//
// MessageId: IDSX_AFX_IDS_PRINTDEFAULT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_PRINTDEFAULT        0x4078F046L

//
// MessageId: IDSX_AFX_IDS_PRINTFILTER
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_PRINTFILTER         0x4078F047L

//
// MessageId: IDSX_AFX_IDS_PRINTCAPTION
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_PRINTCAPTION        0x4078F048L

//
// MessageId: IDSX_AFX_IDS_PRINTTOFILE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_PRINTTOFILE         0x4078F049L

//
// MessageId: IDSX_AFX_IDS_OBJECT_MENUITEM
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_OBJECT_MENUITEM     0x4078F080L

//
// MessageId: IDSX_AFX_IDS_EDIT_VERB
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_EDIT_VERB           0x4078F081L

//
// MessageId: IDSX_AFX_IDS_ACTIVATE_VERB
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_ACTIVATE_VERB       0x4078F082L

//
// MessageId: IDSX_AFX_IDS_CHANGE_LINK
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_CHANGE_LINK         0x4078F083L

//
// MessageId: IDSX_AFX_IDS_AUTO
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_AUTO                0x4078F084L

//
// MessageId: IDSX_AFX_IDS_MANUAL
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_MANUAL              0x4078F085L

//
// MessageId: IDSX_AFX_IDS_FROZEN
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_FROZEN              0x4078F086L

//
// MessageId: IDSX_AFX_IDS_ALL_FILES
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_ALL_FILES           0x4078F087L

//
// MessageId: IDSX_AFX_IDS_SAVE_MENU
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_SAVE_MENU           0x4078F088L

//
// MessageId: IDSX_AFX_IDS_UPDATE_MENU
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_UPDATE_MENU         0x4078F089L

//
// MessageId: IDSX_AFX_IDS_SAVE_AS_MENU
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_SAVE_AS_MENU        0x4078F08AL

//
// MessageId: IDSX_AFX_IDS_SAVE_COPY_AS_MENU
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_SAVE_COPY_AS_MENU   0x4078F08BL

//
// MessageId: IDSX_AFX_IDS_EXIT_MENU
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_EXIT_MENU           0x4078F08CL

//
// MessageId: IDSX_AFX_IDS_UPDATING_ITEMS
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_UPDATING_ITEMS      0x4078F08DL

//
// MessageId: IDSX_AFX_IDS_METAFILE_FORMAT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_METAFILE_FORMAT     0x4078F08EL

//
// MessageId: IDSX_AFX_IDS_DIB_FORMAT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_DIB_FORMAT          0x4078F08FL

//
// MessageId: IDSX_AFX_IDS_BITMAP_FORMAT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_BITMAP_FORMAT       0x4078F090L

//
// MessageId: IDSX_AFX_IDS_LINKSOURCE_FORMAT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_LINKSOURCE_FORMAT   0x4078F091L

//
// MessageId: IDSX_AFX_IDS_EMBED_FORMAT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_EMBED_FORMAT        0x4078F092L

//
// MessageId: IDSX_AFX_IDS_PASTELINKEDTYPE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_PASTELINKEDTYPE     0x4078F094L

//
// MessageId: IDSX_AFX_IDS_UNKNOWNTYPE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_UNKNOWNTYPE         0x4078F095L

//
// MessageId: IDSX_AFX_IDS_RTF_FORMAT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_RTF_FORMAT          0x4078F096L

//
// MessageId: IDSX_AFX_IDS_TEXT_FORMAT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_TEXT_FORMAT         0x4078F097L

//
// MessageId: IDSX_AFX_IDS_INVALID_CURRENCY
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_INVALID_CURRENCY    0x4078F098L

//
// MessageId: IDSX_AFX_IDS_INVALID_DATETIME
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_INVALID_DATETIME    0x4078F099L

//
// MessageId: IDSX_AFX_IDS_INVALID_DATETIMESPAN
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_INVALID_DATETIMESPAN 0x4078F09AL

//
// MessageId: IDSX_AFX_IDP_INVALID_FILENAME
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_INVALID_FILENAME    0x4078F100L

//
// MessageId: IDSX_AFX_IDP_FAILED_TO_OPEN_DOC
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_TO_OPEN_DOC  0x4078F101L

//
// MessageId: IDSX_AFX_IDP_FAILED_TO_SAVE_DOC
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_TO_SAVE_DOC  0x4078F102L

//
// MessageId: IDSX_AFX_IDP_ASK_TO_SAVE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_ASK_TO_SAVE         0x4078F103L

//
// MessageId: IDSX_AFX_IDP_FAILED_TO_CREATE_DOC
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_TO_CREATE_DOC 0x4078F104L

//
// MessageId: IDSX_AFX_IDP_FILE_TOO_LARGE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FILE_TOO_LARGE      0x4078F105L

//
// MessageId: IDSX_AFX_IDP_FAILED_TO_START_PRINT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_TO_START_PRINT 0x4078F106L

//
// MessageId: IDSX_AFX_IDP_FAILED_TO_LAUNCH_HELP
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_TO_LAUNCH_HELP 0x4078F107L

//
// MessageId: IDSX_AFX_IDP_INTERNAL_FAILURE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_INTERNAL_FAILURE    0x4078F108L

//
// MessageId: IDSX_AFX_IDP_COMMAND_FAILURE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_COMMAND_FAILURE     0x4078F109L

//
// MessageId: IDSX_AFX_IDP_FAILED_MEMORY_ALLOC
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_MEMORY_ALLOC 0x4078F10AL

//
// MessageId: IDSX_AFX_IDP_UNREG_DONE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_UNREG_DONE          0x4078F10BL

//
// MessageId: IDSX_AFX_IDP_UNREG_FAILURE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_UNREG_FAILURE       0x4078F10CL

//
// MessageId: IDSX_AFX_IDP_DLL_LOAD_FAILED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_DLL_LOAD_FAILED     0x4078F10DL

//
// MessageId: IDSX_AFX_IDP_DLL_BAD_VERSION
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_DLL_BAD_VERSION     0x4078F10EL

//
// MessageId: IDSX_AFX_IDP_PARSE_INT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_PARSE_INT           0x4078F110L

//
// MessageId: IDSX_AFX_IDP_PARSE_REAL
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_PARSE_REAL          0x4078F111L

//
// MessageId: IDSX_AFX_IDP_PARSE_INT_RANGE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_PARSE_INT_RANGE     0x4078F112L

//
// MessageId: IDSX_AFX_IDP_PARSE_REAL_RANGE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_PARSE_REAL_RANGE    0x4078F113L

//
// MessageId: IDSX_AFX_IDP_PARSE_STRING_SIZE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_PARSE_STRING_SIZE   0x4078F114L

//
// MessageId: IDSX_AFX_IDP_PARSE_RADIO_BUTTON
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_PARSE_RADIO_BUTTON  0x4078F115L

//
// MessageId: IDSX_AFX_IDP_PARSE_BYTE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_PARSE_BYTE          0x4078F116L

//
// MessageId: IDSX_AFX_IDP_PARSE_UINT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_PARSE_UINT          0x4078F117L

//
// MessageId: IDSX_AFX_IDP_PARSE_DATETIME
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_PARSE_DATETIME      0x4078F118L

//
// MessageId: IDSX_AFX_IDP_PARSE_CURRENCY
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_PARSE_CURRENCY      0x4078F119L

//
// MessageId: IDSX_AFX_IDP_PARSE_GUID
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_PARSE_GUID          0x4078F11AL

//
// MessageId: IDSX_AFX_IDP_PARSE_TIME
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_PARSE_TIME          0x4078F11BL

//
// MessageId: IDSX_AFX_IDP_PARSE_DATE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_PARSE_DATE          0x4078F11CL

//
// MessageId: IDSX_AFX_IDP_FAILED_INVALID_FORMAT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_INVALID_FORMAT 0x4078F120L

//
// MessageId: IDSX_AFX_IDP_FAILED_INVALID_PATH
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_INVALID_PATH 0x4078F121L

//
// MessageId: IDSX_AFX_IDP_FAILED_DISK_FULL
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_DISK_FULL    0x4078F122L

//
// MessageId: IDSX_AFX_IDP_FAILED_ACCESS_READ
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_ACCESS_READ  0x4078F123L

//
// MessageId: IDSX_AFX_IDP_FAILED_ACCESS_WRITE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_ACCESS_WRITE 0x4078F124L

//
// MessageId: IDSX_AFX_IDP_FAILED_IO_ERROR_READ
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_IO_ERROR_READ 0x4078F125L

//
// MessageId: IDSX_AFX_IDP_FAILED_IO_ERROR_WRITE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_IO_ERROR_WRITE 0x4078F126L

//
// MessageId: IDSX_AFX_IDP_SCRIPT_ERROR
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SCRIPT_ERROR        0x4078F130L

//
// MessageId: IDSX_AFX_IDP_SCRIPT_DISPATCH_EXCEPTION
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SCRIPT_DISPATCH_EXCEPTION 0x4078F131L

//
// MessageId: IDSX_AFX_IDP_STATIC_OBJECT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_STATIC_OBJECT       0x4078F180L

//
// MessageId: IDSX_AFX_IDP_FAILED_TO_CONNECT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_TO_CONNECT   0x4078F181L

//
// MessageId: IDSX_AFX_IDP_SERVER_BUSY
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SERVER_BUSY         0x4078F182L

//
// MessageId: IDSX_AFX_IDP_BAD_VERB
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_BAD_VERB            0x4078F183L

//
// MessageId: IDSX_AFX_IDS_NOT_DOCOBJECT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_NOT_DOCOBJECT       0x4078F184L

//
// MessageId: IDSX_AFX_IDP_FAILED_TO_NOTIFY
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_TO_NOTIFY    0x4078F185L

//
// MessageId: IDSX_AFX_IDP_FAILED_TO_LAUNCH
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_TO_LAUNCH    0x4078F186L

//
// MessageId: IDSX_AFX_IDP_ASK_TO_UPDATE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_ASK_TO_UPDATE       0x4078F187L

//
// MessageId: IDSX_AFX_IDP_FAILED_TO_UPDATE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_TO_UPDATE    0x4078F188L

//
// MessageId: IDSX_AFX_IDP_FAILED_TO_REGISTER
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_TO_REGISTER  0x4078F189L

//
// MessageId: IDSX_AFX_IDP_FAILED_TO_AUTO_REGISTER
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_TO_AUTO_REGISTER 0x4078F18AL

//
// MessageId: IDSX_AFX_IDP_FAILED_TO_CONVERT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_TO_CONVERT   0x4078F18BL

//
// MessageId: IDSX_AFX_IDP_GET_NOT_SUPPORTED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_GET_NOT_SUPPORTED   0x4078F18CL

//
// MessageId: IDSX_AFX_IDP_SET_NOT_SUPPORTED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SET_NOT_SUPPORTED   0x4078F18DL

//
// MessageId: IDSX_AFX_IDP_ASK_TO_DISCARD
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_ASK_TO_DISCARD      0x4078F18EL

//
// MessageId: IDSX_AFX_IDP_FAILED_TO_CREATE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_TO_CREATE    0x4078F18FL

//
// MessageId: IDSX_AFX_IDP_FAILED_MAPI_LOAD
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_MAPI_LOAD    0x4078F190L

//
// MessageId: IDSX_AFX_IDP_INVALID_MAPI_DLL
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_INVALID_MAPI_DLL    0x4078F191L

//
// MessageId: IDSX_AFX_IDP_FAILED_MAPI_SEND
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FAILED_MAPI_SEND    0x4078F192L

//
// MessageId: IDSX_AFX_IDP_FILE_NONE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FILE_NONE           0x4078F1A0L

//
// MessageId: IDSX_AFX_IDP_FILE_GENERIC
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FILE_GENERIC        0x4078F1A1L

//
// MessageId: IDSX_AFX_IDP_FILE_NOT_FOUND
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FILE_NOT_FOUND      0x4078F1A2L

//
// MessageId: IDSX_AFX_IDP_FILE_BAD_PATH
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FILE_BAD_PATH       0x4078F1A3L

//
// MessageId: IDSX_AFX_IDP_FILE_TOO_MANY_OPEN
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FILE_TOO_MANY_OPEN  0x4078F1A4L

//
// MessageId: IDSX_AFX_IDP_FILE_ACCESS_DENIED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FILE_ACCESS_DENIED  0x4078F1A5L

//
// MessageId: IDSX_AFX_IDP_FILE_INVALID_FILE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FILE_INVALID_FILE   0x4078F1A6L

//
// MessageId: IDSX_AFX_IDP_FILE_REMOVE_CURRENT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FILE_REMOVE_CURRENT 0x4078F1A7L

//
// MessageId: IDSX_AFX_IDP_FILE_DIR_FULL
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FILE_DIR_FULL       0x4078F1A8L

//
// MessageId: IDSX_AFX_IDP_FILE_BAD_SEEK
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FILE_BAD_SEEK       0x4078F1A9L

//
// MessageId: IDSX_AFX_IDP_FILE_HARD_IO
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FILE_HARD_IO        0x4078F1AAL

//
// MessageId: IDSX_AFX_IDP_FILE_SHARING
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FILE_SHARING        0x4078F1ABL

//
// MessageId: IDSX_AFX_IDP_FILE_LOCKING
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FILE_LOCKING        0x4078F1ACL

//
// MessageId: IDSX_AFX_IDP_FILE_DISKFULL
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FILE_DISKFULL       0x4078F1ADL

//
// MessageId: IDSX_AFX_IDP_FILE_EOF
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_FILE_EOF            0x4078F1AEL

//
// MessageId: IDSX_AFX_IDP_ARCH_NONE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_ARCH_NONE           0x4078F1B0L

//
// MessageId: IDSX_AFX_IDP_ARCH_GENERIC
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_ARCH_GENERIC        0x4078F1B1L

//
// MessageId: IDSX_AFX_IDP_ARCH_READONLY
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_ARCH_READONLY       0x4078F1B2L

//
// MessageId: IDSX_AFX_IDP_ARCH_ENDOFFILE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_ARCH_ENDOFFILE      0x4078F1B3L

//
// MessageId: IDSX_AFX_IDP_ARCH_WRITEONLY
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_ARCH_WRITEONLY      0x4078F1B4L

//
// MessageId: IDSX_AFX_IDP_ARCH_BADINDEX
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_ARCH_BADINDEX       0x4078F1B5L

//
// MessageId: IDSX_AFX_IDP_ARCH_BADCLASS
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_ARCH_BADCLASS       0x4078F1B6L

//
// MessageId: IDSX_AFX_IDP_ARCH_BADSCHEMA
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_ARCH_BADSCHEMA      0x4078F1B7L

//
// MessageId: IDSX_AFX_IDS_OCC_SCALEUNITS_PIXELS
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_OCC_SCALEUNITS_PIXELS 0x4078F1C0L

//
// MessageId: IDSX_AFX_IDS_STATUS_FONT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_STATUS_FONT         0x4078F230L

//
// MessageId: IDSX_AFX_IDS_TOOLTIP_FONT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_TOOLTIP_FONT        0x4078F231L

//
// MessageId: IDSX_AFX_IDS_UNICODE_FONT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_UNICODE_FONT        0x4078F232L

//
// MessageId: IDSX_AFX_IDS_MINI_FONT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_MINI_FONT           0x4078F233L

//
// MessageId: IDSX_AFX_IDP_SQL_FIRST
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_FIRST           0x4078F280L

//
// MessageId: IDSX_AFX_IDP_SQL_CONNECT_FAIL
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_CONNECT_FAIL    0x4078F281L

//
// MessageId: IDSX_AFX_IDP_SQL_RECORDSET_FORWARD_ONLY
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_RECORDSET_FORWARD_ONLY 0x4078F282L

//
// MessageId: IDSX_AFX_IDP_SQL_EMPTY_COLUMN_LIST
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_EMPTY_COLUMN_LIST 0x4078F283L

//
// MessageId: IDSX_AFX_IDP_SQL_FIELD_SCHEMA_MISMATCH
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_FIELD_SCHEMA_MISMATCH 0x4078F284L

//
// MessageId: IDSX_AFX_IDP_SQL_ILLEGAL_MODE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_ILLEGAL_MODE    0x4078F285L

//
// MessageId: IDSX_AFX_IDP_SQL_MULTIPLE_ROWS_AFFECTED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_MULTIPLE_ROWS_AFFECTED 0x4078F286L

//
// MessageId: IDSX_AFX_IDP_SQL_NO_CURRENT_RECORD
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_NO_CURRENT_RECORD 0x4078F287L

//
// MessageId: IDSX_AFX_IDP_SQL_NO_ROWS_AFFECTED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_NO_ROWS_AFFECTED 0x4078F288L

//
// MessageId: IDSX_AFX_IDP_SQL_RECORDSET_READONLY
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_RECORDSET_READONLY 0x4078F289L

//
// MessageId: IDSX_AFX_IDP_SQL_SQL_NO_TOTAL
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_SQL_NO_TOTAL    0x4078F28AL

//
// MessageId: IDSX_AFX_IDP_SQL_ODBC_LOAD_FAILED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_ODBC_LOAD_FAILED 0x4078F28BL

//
// MessageId: IDSX_AFX_IDP_SQL_DYNASET_NOT_SUPPORTED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_DYNASET_NOT_SUPPORTED 0x4078F28CL

//
// MessageId: IDSX_AFX_IDP_SQL_SNAPSHOT_NOT_SUPPORTED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_SNAPSHOT_NOT_SUPPORTED 0x4078F28DL

//
// MessageId: IDSX_AFX_IDP_SQL_API_CONFORMANCE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_API_CONFORMANCE 0x4078F28EL

//
// MessageId: IDSX_AFX_IDP_SQL_SQL_CONFORMANCE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_SQL_CONFORMANCE 0x4078F28FL

//
// MessageId: IDSX_AFX_IDP_SQL_NO_DATA_FOUND
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_NO_DATA_FOUND   0x4078F290L

//
// MessageId: IDSX_AFX_IDP_SQL_ROW_UPDATE_NOT_SUPPORTED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_ROW_UPDATE_NOT_SUPPORTED 0x4078F291L

//
// MessageId: IDSX_AFX_IDP_SQL_ODBC_V2_REQUIRED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_ODBC_V2_REQUIRED 0x4078F292L

//
// MessageId: IDSX_AFX_IDP_SQL_NO_POSITIONED_UPDATES
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_NO_POSITIONED_UPDATES 0x4078F293L

//
// MessageId: IDSX_AFX_IDP_SQL_LOCK_MODE_NOT_SUPPORTED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_LOCK_MODE_NOT_SUPPORTED 0x4078F294L

//
// MessageId: IDSX_AFX_IDP_SQL_DATA_TRUNCATED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_DATA_TRUNCATED  0x4078F295L

//
// MessageId: IDSX_AFX_IDP_SQL_ROW_FETCH
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_ROW_FETCH       0x4078F296L

//
// MessageId: IDSX_AFX_IDP_SQL_INCORRECT_ODBC
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_INCORRECT_ODBC  0x4078F297L

//
// MessageId: IDSX_AFX_IDP_SQL_UPDATE_DELETE_FAILED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_UPDATE_DELETE_FAILED 0x4078F298L

//
// MessageId: IDSX_AFX_IDP_SQL_DYNAMIC_CURSOR_NOT_SUPPORTED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_DYNAMIC_CURSOR_NOT_SUPPORTED 0x4078F299L

//
// MessageId: IDSX_AFX_IDP_SQL_FIELD_NOT_FOUND
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_FIELD_NOT_FOUND 0x4078F29AL

//
// MessageId: IDSX_AFX_IDP_SQL_BOOKMARKS_NOT_SUPPORTED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_BOOKMARKS_NOT_SUPPORTED 0x4078F29BL

//
// MessageId: IDSX_AFX_IDP_SQL_BOOKMARKS_NOT_ENABLED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_SQL_BOOKMARKS_NOT_ENABLED 0x4078F29CL

//
// MessageId: IDSX_AFX_IDS_DELETED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_DELETED             0x4078F29DL

//
// MessageId: IDSX_AFX_IDP_DAO_ENGINE_INITIALIZATION
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_DAO_ENGINE_INITIALIZATION 0x4078F2B0L

//
// MessageId: IDSX_AFX_IDP_DAO_DFX_BIND
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_DAO_DFX_BIND        0x4078F2B1L

//
// MessageId: IDSX_AFX_IDP_DAO_OBJECT_NOT_OPEN
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_DAO_OBJECT_NOT_OPEN 0x4078F2B2L

//
// MessageId: IDSX_AFX_IDP_DAO_ROWTOOSHORT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_DAO_ROWTOOSHORT     0x4078F2B3L

//
// MessageId: IDSX_AFX_IDP_DAO_BADBINDINFO
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_DAO_BADBINDINFO     0x4078F2B4L

//
// MessageId: IDSX_AFX_IDP_DAO_COLUMNUNAVAILABLE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDP_DAO_COLUMNUNAVAILABLE 0x4078F2B5L

//
// MessageId: IDSX_AFX_IDS_HTTP_TITLE
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_HTTP_TITLE          0x4078F2D1L

//
// MessageId: IDSX_AFX_IDS_HTTP_NO_TEXT
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_HTTP_NO_TEXT        0x4078F2D2L

//
// MessageId: IDSX_AFX_IDS_HTTP_BAD_REQUEST
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_HTTP_BAD_REQUEST    0x4078F2D3L

//
// MessageId: IDSX_AFX_IDS_HTTP_AUTH_REQUIRED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_HTTP_AUTH_REQUIRED  0x4078F2D4L

//
// MessageId: IDSX_AFX_IDS_HTTP_FORBIDDEN
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_HTTP_FORBIDDEN      0x4078F2D5L

//
// MessageId: IDSX_AFX_IDS_HTTP_NOT_FOUND
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_HTTP_NOT_FOUND      0x4078F2D6L

//
// MessageId: IDSX_AFX_IDS_HTTP_SERVER_ERROR
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_HTTP_SERVER_ERROR   0x4078F2D7L

//
// MessageId: IDSX_AFX_IDS_HTTP_NOT_IMPLEMENTED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_HTTP_NOT_IMPLEMENTED 0x4078F2D8L

//
// MessageId: IDSX_AFX_IDS_CHECKLISTBOX_UNCHECK
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_CHECKLISTBOX_UNCHECK 0x4078F2E1L

//
// MessageId: IDSX_AFX_IDS_CHECKLISTBOX_CHECK
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_CHECKLISTBOX_CHECK  0x4078F2E2L

//
// MessageId: IDSX_AFX_IDS_CHECKLISTBOX_MIXED
//
// MessageText:
//
//  ?
//
#define IDSX_AFX_IDS_CHECKLISTBOX_MIXED  0x4078F2E3L

// EVENTLOG library
//
// MessageId: IDSX_____EVENT_LOG_BEGIN_ID
//
// MessageText:
//
//  !!!!!!!!!!!!!!!!!external identifier!!!!!!!!!!!!!!!!!!!!
//
#define IDSX_____EVENT_LOG_BEGIN_ID      0x4078803FL

//
// MessageId: IDSX_____EVENT_LOG_END_ID
//
// MessageText:
//
//  !!!!!!!!!!!!!!!!!external identifier!!!!!!!!!!!!!!!!!!!!
//
#define IDSX_____EVENT_LOG_END_ID        0x40789800L

//
// MessageId: IDSX_____EVENT_LOG_BEGIN_ID2
//
// MessageText:
//
//  !!!!!!!!!!!!!!!!!external identifier!!!!!!!!!!!!!!!!!!!!
//
#define IDSX_____EVENT_LOG_BEGIN_ID2     0x4078EF1FL

//
// MessageId: IDSX_____EVENT_LOG_END_ID2
//
// MessageText:
//
//  !!!!!!!!!!!!!!!!!external identifier!!!!!!!!!!!!!!!!!!!!
//
#define IDSX_____EVENT_LOG_END_ID2       0x4078EF30L

//
// MessageId: IDSX_IDEV____BEGIN_____
//
// MessageText:
//
//  !!!!!!!!!!!!!!!!! first identifier !!!!!!!!!!!!!!!!!!!!
//
#define IDSX_IDEV____BEGIN_____          0x40768040L

//
// MessageId: IDSX_IDSE_APP_BOARD_DETECTED
//
// MessageText:
//
//  $I1 Phone adapter %s detected
//
#define IDSX_IDSE_APP_BOARD_DETECTED     0x40768048L

//
// MessageId: IDSX_IDSE_APP_LOGON
//
// MessageText:
//
//  $I2 Logon of user: %s
//
#define IDSX_IDSE_APP_LOGON              0x40768049L

//
// MessageId: IDSX_IDSE_CHN_START
//
// MessageText:
//
//  $I1 Recording started
//
#define IDSX_IDSE_CHN_START              0x4076804AL

//
// MessageId: IDSX_IDSE_CHN_STOP
//
// MessageText:
//
//  $I1 Recording stopped
//
#define IDSX_IDSE_CHN_STOP               0x4076804BL

//
// MessageId: IDSX_IDSE_APP_LOGON2
//
// MessageText:
//
//  $I2 %s
//
#define IDSX_IDSE_APP_LOGON2             0x4076804CL

//
// MessageId: IDSX_IDSE_APP_LOGOFF
//
// MessageText:
//
//  $I2 Logged off
//
#define IDSX_IDSE_APP_LOGOFF             0x4076804DL

//
// MessageId: IDSX_IDSE_CHN_CHANGE_PROPERTIES
//
// MessageText:
//
//  $I1 Channel properties were changed
//
#define IDSX_IDSE_CHN_CHANGE_PROPERTIES  0x4076804EL

//
// MessageId: IDSX_IDSE_APP_CHANGE_PROPERTIES
//
// MessageText:
//
//  $I1 Application properties were changed
//
#define IDSX_IDSE_APP_CHANGE_PROPERTIES  0x4076804FL

//
// MessageId: IDSX_IDSE_APP_USER_CHANGE_RIGHTS
//
// MessageText:
//
//  $I2 User rights were changed
//
#define IDSX_IDSE_APP_USER_CHANGE_RIGHTS 0x40768050L

//
// MessageId: IDSX_IDSE_APP_USER_ADDED
//
// MessageText:
//
//  $I2 User account was added
//
#define IDSX_IDSE_APP_USER_ADDED         0x40768051L

//
// MessageId: IDSX_IDSE_APP_USER_PASSWORD_CHANGED
//
// MessageText:
//
//  $I2 User password was changed
//
#define IDSX_IDSE_APP_USER_PASSWORD_CHANGED 0x40768052L

//
// MessageId: IDSX_IDSE_APP_USER_REMOVED
//
// MessageText:
//
//  $I2 User was removed
//
#define IDSX_IDSE_APP_USER_REMOVED       0x40768053L

//
// MessageId: IDSX_IDSE_APP_FREE_SPACE
//
// MessageText:
//
//  $I6 %ld MB free on operational disk
//
#define IDSX_IDSE_APP_FREE_SPACE         0x40768054L

//
// MessageId: IDSX_IDSE_APP_PURGE_SPACE
//
// MessageText:
//
//  $I3 Old files were removed
//
#define IDSX_IDSE_APP_PURGE_SPACE        0x40768055L

//
// MessageId: IDSX_IDSE_APP_PURGE_ERROR
//
// MessageText:
//
//  $E0 ERROR: operational disk cannot be purged!
//
#define IDSX_IDSE_APP_PURGE_ERROR        0x40768056L

//
// MessageId: IDSX_IDSE_APP_PURGE_DIRECTORY
//
// MessageText:
//
//  $I6 Clear directory %s.SRS
//
#define IDSX_IDSE_APP_PURGE_DIRECTORY    0x40768057L

//
// MessageId: IDSX_IDSE_APP_PURGE_INFO
//
// MessageText:
//
//  $I3 %lu files deleted. %lu bytes purged.
//
#define IDSX_IDSE_APP_PURGE_INFO         0x40768058L

//
// MessageId: IDSX_IDSE_APP_PURGE_FILE_ERROR
//
// MessageText:
//
//  $E1 ERROR: file %s cannot be deleted!
//
#define IDSX_IDSE_APP_PURGE_FILE_ERROR   0x40768059L

//
// MessageId: IDSX_IDSE_APP_PURGE_DIR_ERROR
//
// MessageText:
//
//  $E1 ERROR: directory %s cannot be deleted!
//
#define IDSX_IDSE_APP_PURGE_DIR_ERROR    0x4076805AL

//
// MessageId: IDSX_IDSE_APP_ADD_CHANNEL
//
// MessageText:
//
//  $I1 Channels were added
//
#define IDSX_IDSE_APP_ADD_CHANNEL        0x4076805BL

//
// MessageId: IDSX_IDSE_APP_DELETE_CHANNEL
//
// MessageText:
//
//  $I1 Channels were deleted
//
#define IDSX_IDSE_APP_DELETE_CHANNEL     0x4076805CL

//
// MessageId: IDSX_IDSE_APP_PROPERTY_CHANNEL
//
// MessageText:
//
//  $I1 Channels were reconfigured
//
#define IDSX_IDSE_APP_PROPERTY_CHANNEL   0x4076805DL

//
// MessageId: IDSX_IDSE_APP_WATCHDOG_DETECTED
//
// MessageText:
//
//  $I4 Watchdog device initialized %s
//
#define IDSX_IDSE_APP_WATCHDOG_DETECTED  0x4076805EL

//
// MessageId: IDSX_IDSE_APP_PHONE_UNEXPECTED_COMMAND
//
// MessageText:
//
//  $I4 Unexpected command on phone adapter %s
//
#define IDSX_IDSE_APP_PHONE_UNEXPECTED_COMMAND 0x4076805FL

//
// MessageId: IDSX_IDSE_APP_PHONE_UNRECOGNIZED_COMMAND
//
// MessageText:
//
//  $E4 Unrecognized command on phone adapter %s
//
#define IDSX_IDSE_APP_PHONE_UNRECOGNIZED_COMMAND 0x40768060L

//
// MessageId: IDSX_IDSE_APP_PHONE_UNRECOGNIZED_COMMAND2
//
// MessageText:
//
//  $E4   unrecognized %lu commands of %lu total
//
#define IDSX_IDSE_APP_PHONE_UNRECOGNIZED_COMMAND2 0x40768061L

//
// MessageId: IDSX_IDSE_APP_PHONE_REJECT
//
// MessageText:
//
//  $I6 Skipped query cycle on phone adapter %s
//
#define IDSX_IDSE_APP_PHONE_REJECT       0x40768062L

//
// MessageId: IDSX_IDSE_APP_PHONE_REJECT2
//
// MessageText:
//
//  $I6   %lu cycles skipped total
//
#define IDSX_IDSE_APP_PHONE_REJECT2      0x40768063L

//
// MessageId: IDSX_IDSE_APP_CPU_OVERLOADED
//
// MessageText:
//
//  $W0 CPU loading is %lu%%
//
#define IDSX_IDSE_APP_CPU_OVERLOADED     0x40768064L

//
// MessageId: IDSX_IDSE_APP_PHONE_LOST_QUERIES
//
// MessageText:
//
//  $I6   %lu%% queries lost
//
#define IDSX_IDSE_APP_PHONE_LOST_QUERIES 0x40768065L

//
// MessageId: IDSX_IDSE_APP_VERSION
//
// MessageText:
//
//  $I1 Version: %s
//
#define IDSX_IDSE_APP_VERSION            0x40768066L

//
// MessageId: IDSX_IDSE_APP_SERIAL_NUMBER
//
// MessageText:
//
//  $I2 Serial number: %s
//
#define IDSX_IDSE_APP_SERIAL_NUMBER      0x40768067L

//
// MessageId: IDSX_IDSE_APP_CHANGE_ENVIRONMENT
//
// MessageText:
//
//  $I1 Computer configuration has been changed
//
#define IDSX_IDSE_APP_CHANGE_ENVIRONMENT 0x40768068L

//
// MessageId: IDSX_IDSE_APP_ANY_STRING
//
// MessageText:
//
//  $I1 %s
//
#define IDSX_IDSE_APP_ANY_STRING         0x40768069L

//
// MessageId: IDSX_IDSE_APP_ANY_STRING_AS_WARNING
//
// MessageText:
//
//  $W1 %s
//
#define IDSX_IDSE_APP_ANY_STRING_AS_WARNING 0x4076806AL

//
// MessageId: IDSX_IDSE_CHN_AON_DETECT
//
// MessageText:
//
//  $I7 Incoming phone number detecting %B
//
#define IDSX_IDSE_CHN_AON_DETECT         0x40768084L

//
// MessageId: IDSX_IDSE_CHN_AON_DETECT2
//
// MessageText:
//
//  $I7 Incoming phone number detecting (2) %B
//
#define IDSX_IDSE_CHN_AON_DETECT2        0x40768085L

//
// MessageId: IDSX_IDSE_CHN_AON_DETECT_END
//
// MessageText:
//
//  $I4 Incoming phone number detected %B
//
#define IDSX_IDSE_CHN_AON_DETECT_END     0x40768086L

//
// MessageId: IDSX_IDSE_CHN_AON_DETECT_END2
//
// MessageText:
//
//  $I4 Incoming phone number detected (2) %B
//
#define IDSX_IDSE_CHN_AON_DETECT_END2    0x40768087L

//
// MessageId: IDSX_IDSE_CHN_AON_DETECT_FAILURE
//
// MessageText:
//
//  $I6 Incoming phone number detection failure
//
#define IDSX_IDSE_CHN_AON_DETECT_FAILURE 0x40768088L

//
// MessageId: IDSX_IDSE_CHN_AON_DETECT_FAILURE2
//
// MessageText:
//
//  $I6 Incoming phone number detection failure (2)
//
#define IDSX_IDSE_CHN_AON_DETECT_FAILURE2 0x40768089L

//
// MessageId: IDSX_IDSE_CHN_AON_DETECT_START
//
// MessageText:
//
//  $I7 Phone number detection...
//
#define IDSX_IDSE_CHN_AON_DETECT_START   0x4076808AL

//
// MessageId: IDSX_IDSE_CHN_AON_DETECT_START2
//
// MessageText:
//
//  $I7 Incoming phone number detection (2)...
//
#define IDSX_IDSE_CHN_AON_DETECT_START2  0x4076808BL

//
// MessageId: IDSX_IDSE_CHN_ERROR
//
// MessageText:
//
//  $E0 ERROR: Channel failure!
//
#define IDSX_IDSE_CHN_ERROR              0x4076808CL

//
// MessageId: IDSX_IDSE_CHN_NO_ERROR
//
// MessageText:
//
//  $W0 Channel functions properly
//
#define IDSX_IDSE_CHN_NO_ERROR           0x4076808DL

//
// MessageId: IDSX_IDSE_LOGRECREATE
//
// MessageText:
//
//  $E0 Event log error. Dumping was performed. Event log was renewed.
//
#define IDSX_IDSE_LOGRECREATE            0x4076808EL

//
// MessageId: IDSX_IDSE_CHN_DTMF_DETECT
//
// MessageText:
//
//  $I7 Outcoming phone number detection %B
//
#define IDSX_IDSE_CHN_DTMF_DETECT        0x4076808FL

//
// MessageId: IDSX_IDSE_CHN_DTMF_DETECT_END
//
// MessageText:
//
//  $I4 Outcoming phone number detected %B
//
#define IDSX_IDSE_CHN_DTMF_DETECT_END    0x40768090L

//
// MessageId: IDSX_IDSE_CHN_DTMF_DETECT_FAILURE
//
// MessageText:
//
//  $I6 Outcoming phone number detection failure
//
#define IDSX_IDSE_CHN_DTMF_DETECT_FAILURE 0x40768091L

//
// MessageId: IDSX_IDSE_CHN_PULSE_DETECT
//
// MessageText:
//
//  $I6 Outcoming phone number detection %B (Dial Pulsing)
//
#define IDSX_IDSE_CHN_PULSE_DETECT       0x40768092L

//
// MessageId: IDSX_IDSE_CHN_PULSE_DETECT_END
//
// MessageText:
//
//  $I4 Outcoming phone number detected %B (Dial Pulsing)
//
#define IDSX_IDSE_CHN_PULSE_DETECT_END   0x40768093L

//
// MessageId: IDSX_IDSE_CHN_PULSE_FAILURE
//
// MessageText:
//
//  $I6 Outcoming phone number detection failure (Dial Pulsing)
//
#define IDSX_IDSE_CHN_PULSE_FAILURE      0x40768094L

//
// MessageId: IDSX_IDSE_APP_VOX_DETECT_START
//
// MessageText:
//
//  $I1 Voice activation enabled %s
//
#define IDSX_IDSE_APP_VOX_DETECT_START   0x40768095L

//
// MessageId: IDSX_IDSE_APP_VOX_DETECT_STOP
//
// MessageText:
//
//  $I1 Voice activation disabled
//
#define IDSX_IDSE_APP_VOX_DETECT_STOP    0x40768096L

//
// MessageId: IDSX_IDSE_APP_THREAD
//
// MessageText:
//
//  $I7 Thread %8.8X %Z.\nstarted\nterminated\naborted
//
#define IDSX_IDSE_APP_THREAD             0x40768097L

//
// MessageId: IDSX_IDSE_APP_THREAD_CONVERSION
//
// MessageText:
//
//  $I7 Conversion thread %8.8X %Z.\nstarted\nterminated\naborted
//
#define IDSX_IDSE_APP_THREAD_CONVERSION  0x40768098L

//
// MessageId: IDSX_IDSE_CHN_THREAD_CHANNEL
//
// MessageText:
//
//  $I7 Channel thread %8.8X %Z.\nstarted\nterminated\naborted
//
#define IDSX_IDSE_CHN_THREAD_CHANNEL     0x40768099L

//
// MessageId: IDSX_IDSE_APP_THREAD_LINE
//
// MessageText:
//
//  $I7 Line thread %8.8X %Z.\nstarted\nterminated\naborted
//
#define IDSX_IDSE_APP_THREAD_LINE        0x4076809AL

//
// MessageId: IDSX_IDSE_APP_THREAD_MAIN
//
// MessageText:
//
//  $I7 Main thread %8.8X %Z.\nstarted\nterminated\naborted
//
#define IDSX_IDSE_APP_THREAD_MAIN        0x4076809BL

//
// MessageId: IDSX_IDSE_APP_THREAD_DEVICE
//
// MessageText:
//
//  $I7 Device thread %8.8X %Z.\nstarted\nterminating...\naborted
//
#define IDSX_IDSE_APP_THREAD_DEVICE      0x4076809CL

//
// MessageId: IDSX_IDSE_APP_THREAD_TIMER
//
// MessageText:
//
//  $I7 Timer thread %8.8X %Z.\nstarted\nterminating...\naborted
//
#define IDSX_IDSE_APP_THREAD_TIMER       0x4076809DL

//
// MessageId: IDSX_IDSE_APP_NSP_INIT_FAILURE
//
// MessageText:
//
//  $I7 The NSP library is not found
//
#define IDSX_IDSE_APP_NSP_INIT_FAILURE   0x4076809EL

//
// MessageId: IDSX_IDSE_APP_NSP_INIT_DONE
//
// MessageText:
//
//  $I7 The NSP library is loaded
//
#define IDSX_IDSE_APP_NSP_INIT_DONE      0x4076809FL

//
// MessageId: IDSX_IDSE_APP_THREAD_HOOK
//
// MessageText:
//
//  $I7 Hook thread %8.8X %Z.\nstarted\nterminating...\naborted
//
#define IDSX_IDSE_APP_THREAD_HOOK        0x407680A0L

//
// MessageId: IDSX_IDSE_APP_THREAD_ABORT
//
// MessageText:
//
//  $W1 Thread %8.8X aborted.
//
#define IDSX_IDSE_APP_THREAD_ABORT       0x407680A1L

//
// MessageId: IDSX_IDSE_CHN_MUST_SENT_COMMAND
//
// MessageText:
//
//  $W2 After %d retries to this channel must be sent command %Z.\nSTART\nSTOP
//
#define IDSX_IDSE_CHN_MUST_SENT_COMMAND  0x407680A2L

//
// MessageId: IDSX_IDSE_APP_LINE_STATUS_CHANGED
//
// MessageText:
//
//  $I7 Lines status changed: %Y (%.0dcurrent=%8.8X).
//
#define IDSX_IDSE_APP_LINE_STATUS_CHANGED 0x407680A3L

//
// MessageId: IDSX_IDSE_CHN_ATTACHED_TO_LINE
//
// MessageText:
//
//  $I6 Channel %.0d attached to line %d
//
#define IDSX_IDSE_CHN_ATTACHED_TO_LINE   0x407680A4L

//
// MessageId: IDSX_IDSE_APP_ACM_INIT_DONE
//
// MessageText:
//
//  $I7 ACM loaded
//
#define IDSX_IDSE_APP_ACM_INIT_DONE      0x407680A5L

//
// MessageId: IDSX_IDSE_APP_LINE_ATTACHNMENT_CHANGED
//
// MessageText:
//
//  $I4 Lines attachment changed: %Y (%.0dcurrent=%8.8X).
//
#define IDSX_IDSE_APP_LINE_ATTACHNMENT_CHANGED 0x407680A6L

//
// MessageId: IDSX_IDSE_CHN_RENAME_RECORD_ERROR
//
// MessageText:
//
//  $E1 ERROR: record %B cannot be renamed
//
#define IDSX_IDSE_CHN_RENAME_RECORD_ERROR 0x407680A7L

//
// MessageId: IDSX_IDSE_CHN_OS_ERROR
//
// MessageText:
//
//  $E1 ERROR : OS code = %d
//
#define IDSX_IDSE_CHN_OS_ERROR           0x407680A8L

//
// MessageId: IDSX_IDSE_CHN_WAVE_ERROR
//
// MessageText:
//
//  $E0 ERROR: %Z\nThere's no signal!\nLong silence
//
#define IDSX_IDSE_CHN_WAVE_ERROR         0x407680A9L

//
// MessageId: IDSX_IDSE_CHN_WAVE_NO_ERROR
//
// MessageText:
//
//  $W0 %Z\nSignal detected\nSilence broken\nOverload of sound track
//
#define IDSX_IDSE_CHN_WAVE_NO_ERROR      0x407680AAL

//
// MessageId: IDSX_IDEV____COMMANDS____
//
// MessageText:
//
//  !!!!!!!!!!!!!!!!! commands start identifier !!!!!!!!!!!!!!!!!!!!
//
#define IDSX_IDEV____COMMANDS____        0x40769000L

//
// MessageId: IDSX_IDSQ_TIME
//
// MessageText:
//
//  IDSQ_TIME
//
#define IDSX_IDSQ_TIME                   0x40769001L

//
// MessageId: IDSX_IDSA_TIME
//
// MessageText:
//
//  IDSA_TIME: %ld milliseconds lost
//
#define IDSX_IDSA_TIME                   0x40769002L

//
// MessageId: IDSX_IDSQ_CHN_STATE
//
// MessageText:
//
//  IDSQ_CHN_STATE
//
#define IDSX_IDSQ_CHN_STATE              0x40769003L

//
// MessageId: IDSX_IDSA_CHN_STATE
//
// MessageText:
//
//  IDSA_CHN_STATE: %ld state
//
#define IDSX_IDSA_CHN_STATE              0x40769004L

//
// MessageId: IDSX_IDSQ_CHN_CHANGE_STATE
//
// MessageText:
//
//  IDSQ_CHN_CHANGE_STATE
//
#define IDSX_IDSQ_CHN_CHANGE_STATE       0x40769005L

//
// MessageId: IDSX_IDSA_CHN_CHANGE_STATE
//
// MessageText:
//
//  IDSA_CHN_CHANGE_STATE: %lu new state, %lu old state
//
#define IDSX_IDSA_CHN_CHANGE_STATE       0x40769006L

//
// MessageId: IDSX_IDSQ_ATTACH_EVENTS_LOG
//
// MessageText:
//
//  IDSQ_ATTACH_EVENTS_LOG
//
#define IDSX_IDSQ_ATTACH_EVENTS_LOG      0x40769007L

//
// MessageId: IDSX_IDSA_ATTACH_EVENTS_LOG
//
// MessageText:
//
//  IDSA_ATTACH_EVENTS_LOG
//
#define IDSX_IDSA_ATTACH_EVENTS_LOG      0x40769008L

//
// MessageId: IDSX_IDSQ_DETACH_EVENTS_LOG
//
// MessageText:
//
//  IDSQ_DETACH_EVENTS_LOG
//
#define IDSX_IDSQ_DETACH_EVENTS_LOG      0x40769009L

//
// MessageId: IDSX_IDSA_DETACH_EVENTS_LOG
//
// MessageText:
//
//  IDSA_DETACH_EVENTS_LOG
//
#define IDSX_IDSA_DETACH_EVENTS_LOG      0x4076900AL

//
// MessageId: IDSX_IDSQ_INFO
//
// MessageText:
//
//  IDSQ_INFO
//
#define IDSX_IDSQ_INFO                   0x4076900BL

//
// MessageId: IDSX_IDSA_INFO
//
// MessageText:
//
//  IDSA_INFO
//
#define IDSX_IDSA_INFO                   0x4076900CL

//
// MessageId: IDSX_IDEV____END____
//
// MessageText:
//
//  !!!!!!!!!!!!!!!!! last identifier !!!!!!!!!!!!!!!!!!!!
//
#define IDSX_IDEV____END____             0x407697FFL

//
// MessageId: IDSX_IDEV____BEGIN_____2
//
// MessageText:
//
//  !!!!!!!!!!!!!!!!! first identifier !!!!!!!!!!!!!!!!!!!!
//
#define IDSX_IDEV____BEGIN_____2         0x4076EF20L

//
// MessageId: IDSX_IDEV_APPSTART
//
// MessageText:
//
//  $I0 Application started
//
#define IDSX_IDEV_APPSTART               0x4076EF27L

//
// MessageId: IDSX_IDEV_APPSTOP
//
// MessageText:
//
//  $I0 Application terminated
//
#define IDSX_IDEV_APPSTOP                0x4076EF28L

//
// MessageId: IDSX_IDEV____END____2
//
// MessageText:
//
//  !!!!!!!!!!!!!!!!! last identifier !!!!!!!!!!!!!!!!!!!!
//
#define IDSX_IDEV____END____2            0x4076EF2FL

// CPasswordsDialog
//
// MessageId: IDSX_IDS_PASSWORD_DIALOG
//
// MessageText:
//
//  Enter credentials:
//
#define IDSX_IDS_PASSWORD_DIALOG         0x40780FDFL

//
// MessageId: IDSX_IDS_CURRENT_USER
//
// MessageText:
//
//  Current user:
//
#define IDSX_IDS_CURRENT_USER            0x40780FE0L

//
// MessageId: IDSX_IDS_DOMAIN
//
// MessageText:
//
//  Domain:
//
#define IDSX_IDS_DOMAIN                  0x40780FE1L

//
// MessageId: IDSX_IDS_USER
//
// MessageText:
//
//  User:
//
#define IDSX_IDS_USER                    0x40780FE2L

//
// MessageId: IDSX_IDS_PASSWORD
//
// MessageText:
//
//  Password:
//
#define IDSX_IDS_PASSWORD                0x40780FE3L

//
// MessageId: IDSX_IDS_PASSWORD_RETYPE
//
// MessageText:
//
//  Confirm password:
//
#define IDSX_IDS_PASSWORD_RETYPE         0x40780FE4L

//
// MessageId: IDSX_IDS_PASSWORD_IGNORE
//
// MessageText:
//
//  Ignore password checking
//
#define IDSX_IDS_PASSWORD_IGNORE         0x40780FE5L

//
// MessageId: IDSX_IDS_PASSWORD_IS_BAD
//
// MessageText:
//
//  The password is not recognized by the system. Enter the correct password!
//
#define IDSX_IDS_PASSWORD_IS_BAD         0x40780FE6L

//
// MessageId: IDSX_IDS_ALL
//
// MessageText:
//
//  All
//
#define IDSX_IDS_ALL                     0x40780FE7L

// DIALOG - IDD_MUTIMEDIA_EXPORT
//
// MessageId: IDSX_IDD_MULTIMEDIA_EXPORT
//
// MessageText:
//
//  Export
//
#define IDSX_IDD_MULTIMEDIA_EXPORT       0x4075D900L

//
// MessageId: IDSX_IDC_STATIC_SOURCE_DATA
//
// MessageText:
//
//  Source data
//
#define IDSX_IDC_STATIC_SOURCE_DATA      0x4075D9C5L

//
// MessageId: IDSX_IDC_CHECK_ALL_RECORD
//
// MessageText:
//
//  all
//
#define IDSX_IDC_CHECK_ALL_RECORD        0x4075D9A2L

//
// MessageId: IDSX_IDC_DATETIMEPICKER_START
//
// MessageText:
//
//  DateTimePicker2
//
#define IDSX_IDC_DATETIMEPICKER_START    0x4075D929L

//
// MessageId: IDSX_IDC_DATETIMEPICKER_STOP
//
// MessageText:
//
//  DateTimePicker2
//
#define IDSX_IDC_DATETIMEPICKER_STOP     0x4075D92BL

//
// MessageId: IDSX_IDC_STATIC_PERIOD
//
// MessageText:
//
//  Interval:
//
#define IDSX_IDC_STATIC_PERIOD           0x4075D9C6L

//
// MessageId: IDSX_IDC_STATIC_BEG
//
// MessageText:
//
//  start:
//
#define IDSX_IDC_STATIC_BEG              0x4075D9C7L

//
// MessageId: IDSX_IDC_CHECK_SELECTED_RECORD
//
// MessageText:
//
//  selection
//
#define IDSX_IDC_CHECK_SELECTED_RECORD   0x4075D9B2L

//
// MessageId: IDSX_IDC_CHECK_ALL_AUDIO
//
// MessageText:
//
//  all
//
#define IDSX_IDC_CHECK_ALL_AUDIO         0x4075D9A4L

//
// MessageId: IDSX_IDC_COMBO_AUDIO_MIC
//
// MessageText:
//
//  
//
#define IDSX_IDC_COMBO_AUDIO_MIC         0x4075D9A3L

//
// MessageId: IDSX_IDC_STATIC_MICROPHONE
//
// MessageText:
//
//  Microphone:
//
#define IDSX_IDC_STATIC_MICROPHONE       0x4075D9C9L

//
// MessageId: IDSX_IDC_CHECK_ALL_VIDEO
//
// MessageText:
//
//  all
//
#define IDSX_IDC_CHECK_ALL_VIDEO         0x4075D9A6L

//
// MessageId: IDSX_IDC_COMBO_VIDEO_CAM
//
// MessageText:
//
//  
//
#define IDSX_IDC_COMBO_VIDEO_CAM         0x4075D9A5L

//
// MessageId: IDSX_IDC_STATIC_CAMERA
//
// MessageText:
//
//  Camera:
//
#define IDSX_IDC_STATIC_CAMERA           0x4075D9CAL

//
// MessageId: IDSX_IDC_STATIC_AUDIO
//
// MessageText:
//
//  Audio
//
#define IDSX_IDC_STATIC_AUDIO            0x4075D9CBL

//
// MessageId: IDSX_IDC_CHECK_SAME_AUDIO
//
// MessageText:
//
//  original
//
#define IDSX_IDC_CHECK_SAME_AUDIO        0x4075D9A8L

//
// MessageId: IDSX_IDC_COMBO_AUDIO_CODEC
//
// MessageText:
//
//  mp3\naac\nadpcm_ima_wav\npcm_s16le
//
#define IDSX_IDC_COMBO_AUDIO_CODEC       0x4075D9A7L

//
// MessageId: IDSX_IDC_STATIC_ACODEC
//
// MessageText:
//
//  Codec:
//
#define IDSX_IDC_STATIC_ACODEC           0x4075D9BEL

//
// MessageId: IDSX_IDC_MIN_AUD
//
// MessageText:
//
//  minimal
//
#define IDSX_IDC_MIN_AUD                 0x4075D9B6L

//
// MessageId: IDSX_IDC_MAX_AUD
//
// MessageText:
//
//  maximal
//
#define IDSX_IDC_MAX_AUD                 0x4075D9B7L

//
// MessageId: IDSX_IDC_SLIDER_COMPRESSION_AUDIO
//
// MessageText:
//
//  Slider1
//
#define IDSX_IDC_SLIDER_COMPRESSION_AUDIO 0x4075D9A9L

//
// MessageId: IDSX_IDC_AUDIO_COMPRESS_COMBO
//
// MessageText:
//
//  Minimal\nMiddle\nMaximal
//
#define IDSX_IDC_AUDIO_COMPRESS_COMBO    0x4075D9B5L

//
// MessageId: IDSX_IDC_EDIT_COMPRESSION_AUDIO
//
// MessageText:
//
//  
//
#define IDSX_IDC_EDIT_COMPRESSION_AUDIO  0x4075D912L

//
// MessageId: IDSX_IDC_STATIC_ACOMPRESS
//
// MessageText:
//
//  The degree of compression:
//
#define IDSX_IDC_STATIC_ACOMPRESS        0x4075D9CEL

//
// MessageId: IDSX_IDC_EDIT_AUDIO_FORMAT
//
// MessageText:
//
//  
//
#define IDSX_IDC_EDIT_AUDIO_FORMAT       0x4075D9AAL

//
// MessageId: IDSX_IDC_STATIC_AFORMAT
//
// MessageText:
//
//  Format:
//
#define IDSX_IDC_STATIC_AFORMAT          0x4075D9D0L

//
// MessageId: IDSX_IDC_USE_PLAYBACK_SETTINGS
//
// MessageText:
//
//  Use playback options
//
#define IDSX_IDC_USE_PLAYBACK_SETTINGS   0x4075D9C2L

//
// MessageId: IDSX_IDC_STATIC_VIDEO
//
// MessageText:
//
//  Video
//
#define IDSX_IDC_STATIC_VIDEO            0x4075D9CCL

//
// MessageId: IDSX_IDC_CHECK_SAME_VIDEO
//
// MessageText:
//
//  original
//
#define IDSX_IDC_CHECK_SAME_VIDEO        0x4075D9AEL

//
// MessageId: IDSX_IDC_COMBO_VIDEO_CODEC
//
// MessageText:
//
//  MPEG-2
//
#define IDSX_IDC_COMBO_VIDEO_CODEC       0x4075D9ADL

//
// MessageId: IDSX_IDC_STATIC_VCODEC
//
// MessageText:
//
//  Codec:
//
#define IDSX_IDC_STATIC_VCODEC           0x4075D9BFL

//
// MessageId: IDSX_IDC_COMBO_VIDEO_CROP
//
// MessageText:
//
//  original\nup left quarter\nup right quarter\ndown left quarter\ndown right quarter
//
#define IDSX_IDC_COMBO_VIDEO_CROP        0x4075D9B3L

//
// MessageId: IDSX_IDC_STATIC_WINDOW
//
// MessageText:
//
//  Window:
//
#define IDSX_IDC_STATIC_WINDOW           0x4075D9BCL

//
// MessageId: IDSX_IDC_COMBO_VIDEO_RESOLUTION
//
// MessageText:
//
//  original\nnormal\neconomical\n128x96\n176x144\n320x240
//
#define IDSX_IDC_COMBO_VIDEO_RESOLUTION  0x4075D9B1L

//
// MessageId: IDSX_IDC_STATIC_QUALITY
//
// MessageText:
//
//  Quality:
//
#define IDSX_IDC_STATIC_QUALITY          0x4075D9BDL

//
// MessageId: IDSX_IDC_MIN_VID
//
// MessageText:
//
//  minimal
//
#define IDSX_IDC_MIN_VID                 0x4075D9BAL

//
// MessageId: IDSX_IDC_MAX_VID
//
// MessageText:
//
//  maximal
//
#define IDSX_IDC_MAX_VID                 0x4075D9BBL

//
// MessageId: IDSX_IDC_SLIDER_COMPRESSION_VIDEO
//
// MessageText:
//
//  Slider1
//
#define IDSX_IDC_SLIDER_COMPRESSION_VIDEO 0x4075D9AFL

//
// MessageId: IDSX_IDC_VIDEO_COMPRESS_COMBO
//
// MessageText:
//
//  Minimal\nMiddle\nMaximal
//
#define IDSX_IDC_VIDEO_COMPRESS_COMBO    0x4075D9B8L

//
// MessageId: IDSX_IDC_EDIT_COMPRESSION_VIDEO
//
// MessageText:
//
//  
//
#define IDSX_IDC_EDIT_COMPRESSION_VIDEO  0x4075D911L

//
// MessageId: IDSX_IDC_STATIC_VCOMPRESS
//
// MessageText:
//
//  The degree of compression:
//
#define IDSX_IDC_STATIC_VCOMPRESS        0x4075D9CFL

//
// MessageId: IDSX_IDC_EDIT_VIDEO_FORMAT
//
// MessageText:
//
//  
//
#define IDSX_IDC_EDIT_VIDEO_FORMAT       0x4075D9B0L

//
// MessageId: IDSX_IDC_STATIC_VFORMAT
//
// MessageText:
//
//  Format:
//
#define IDSX_IDC_STATIC_VFORMAT          0x4075D9D1L

//
// MessageId: IDSX_IDC_STATIC_TEXT
//
// MessageText:
//
//  Text
//
#define IDSX_IDC_STATIC_TEXT             0x4075D9CDL

//
// MessageId: IDSX_IDC_COMBO_TEXT_CODEC
//
// MessageText:
//
//  
//
#define IDSX_IDC_COMBO_TEXT_CODEC        0x4075D9B4L

//
// MessageId: IDSX_IDC_STATIC_TEXT_TYPE
//
// MessageText:
//
//  Type:
//
#define IDSX_IDC_STATIC_TEXT_TYPE        0x4075D9D2L

//
// MessageId: IDSX_IDC_EXPORT_TEXT
//
// MessageText:
//
//  Text export
//
#define IDSX_IDC_EXPORT_TEXT             0x4075D9C4L

//
// MessageId: IDSX_IDC_STATIC_RESULT
//
// MessageText:
//
//  Result
//
#define IDSX_IDC_STATIC_RESULT           0x4075D9D3L

//
// MessageId: IDSX_IDC_COMBO_CONTAINER
//
// MessageText:
//
//  AVI\nFLV\nSWF\nMOV\nVOB\nMP4\nWAV\nMP3\nM4A
//
#define IDSX_IDC_COMBO_CONTAINER         0x4075D9ABL

//
// MessageId: IDSX_IDC_STATIC_FILE_TYPE
//
// MessageText:
//
//  File type:
//
#define IDSX_IDC_STATIC_FILE_TYPE        0x4075D9D4L

//
// MessageId: IDSX_IDC_EDIT_FILE_PATH
//
// MessageText:
//
//  
//
#define IDSX_IDC_EDIT_FILE_PATH          0x4075D9ACL

//
// MessageId: IDSX_IDC_STATIC_FILE
//
// MessageText:
//
//  File:
//
#define IDSX_IDC_STATIC_FILE             0x4075D9D5L

//
// MessageId: IDSX_IDC_BUTTON_BROWSE_FILE
//
// MessageText:
//
//  ...
//
#define IDSX_IDC_BUTTON_BROWSE_FILE      0x4075D9A1L

//
// MessageId: IDSX_IDC_STATIC_SIZELB
//
// MessageText:
//
//  Size, MB: 
//
#define IDSX_IDC_STATIC_SIZELB           0x4075D9C0L

//
// MessageId: IDSX_IDC_STATIC_OUTSIZE
//
// MessageText:
//
//  0
//
#define IDSX_IDC_STATIC_OUTSIZE          0x4075D9C1L

//
// MessageId: IDSX_IDC_SINGLE_FILE
//
// MessageText:
//
//  Single file
//
#define IDSX_IDC_SINGLE_FILE             0x4075D9C3L

//
// MessageId: IDSX_IDC_SAVE_XML
//
// MessageText:
//
//  ->XML...
//
#define IDSX_IDC_SAVE_XML                0x4075D901L

//
// MessageId: IDSX_IDC_BUTTON_PLAY
//
// MessageText:
//
//  >
//
#define IDSX_IDC_BUTTON_PLAY             0x4075D914L

//
// MessageId: IDSX_IDC_ADVANCED_MODE
//
// MessageText:
//
//  Expert
//
#define IDSX_IDC_ADVANCED_MODE           0x4075D9B9L

