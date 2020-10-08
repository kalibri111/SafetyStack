//
// Created by kalibri on 05.10.2020.
//

#ifndef SAFETYSTACK_SETTINGS_H
#define SAFETYSTACK_SETTINGS_H



/*
 * define security settings here, possible:
 * CANARY_PROTECT    - canary protecting
 * HASH_PROTECT      - checking check sum
 * */
#define CANARY_PROTECT
#define HASH_PROTECT

/*
 * log file path
 * */

const char* LOG_FILE_PATH = "../log/log.html";


#endif //SAFETYSTACK_SETTINGS_H
