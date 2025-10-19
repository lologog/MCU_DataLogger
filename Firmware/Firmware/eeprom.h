/*
 * eeprom.h
 *
 * Created: 19.10.2025 14:34:41
 * Author: Krzysztof Tomicki
 * Description: Manage data stored in EEPROM
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

void eep_load(void);
void eep_save(void);
void check_eep_load_data(void);

#endif /* EEPROM_H_ */