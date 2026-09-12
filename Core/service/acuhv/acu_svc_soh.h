#ifndef acu_svc_soh_h_
#define acu_svc_soh_h_

#define ACU_CELL_CAPACITY_AH                        3.0f
#define ACU_PACK_SERIES_CELL_COUNT                  (26.0f * 5.0f) // 5 segments of 26 series cells each.
#define ACU_PACK_PARALLEL_CELL_COUNT                5.0f
#define ACU_PACK_VOLTAGE_FULLY_CHARGED_V            4.2f*(ACU_PACK_SERIES_CELL_COUNT)
#define ACU_PACK_VOLTAGE_EMPTY_V                    2.5f*(ACU_PACK_SERIES_CELL_COUNT)
#define ACU_PACK_CAPACITY_AH                        (ACU_CELL_CAPACITY_AH * ACU_PACK_PARALLEL_CELL_COUNT)
#define ACU_PACK_ENERGY_WH                          (ACU_PACK_CAPACITY_AH * ACU_PACK_VOLTAGE_FULLY_CHARGED_V)

void acu_svc_init_acu_energy_state(void);
void acu_svc_update_acu_energy_state(void);

#endif /* acu_svc_soh_h_ */