char *anims2str[]  = {
"FACE_TALK0",
"FACE_TALK1",
"FACE_TALK2",
"FACE_TALK3",
"FACE_TALK4",
"FACE_ALERT",
"FACE_SMILE",
"FACE_FROWN",
"FACE_DEAD",
"BOTH_DEATH1",
"BOTH_DEATH2",
"BOTH_DEATH3",
"BOTH_DEATH4",
"BOTH_DEATH5",
"BOTH_DEATH6",
"BOTH_DEATH7",
"BOTH_DEATH8",
"BOTH_DEATH9",
"BOTH_DEATH10",
"BOTH_DEATH11",
"BOTH_DEATH12",
"BOTH_DEATH13",
"BOTH_DEATH14",
"BOTH_DEATH15",
"BOTH_DEATH16",
"BOTH_DEATH17",
"BOTH_DEATH18",
"BOTH_DEATH19",
"BOTH_DEATH20",
"BOTH_DEATH21",
"BOTH_DEATH22",
"BOTH_DEATH23",
"BOTH_DEATH24",
"BOTH_DEATH25",
"BOTH_DEATHFORWARD1",
"BOTH_DEATHFORWARD2",
"BOTH_DEATHFORWARD3",
"BOTH_DEATHBACKWARD1",
"BOTH_DEATHBACKWARD2",
"BOTH_DEATH1IDLE",
"BOTH_LYINGDEATH1",
"BOTH_STUMBLEDEATH1",
"BOTH_FALLDEATH1",
"BOTH_FALLDEATH1INAIR",
"BOTH_FALLDEATH1LAND",
"BOTH_DEATH_ROLL",
"BOTH_DEATH_FLIP",
"BOTH_DEATH_SPIN_90_R",
"BOTH_DEATH_SPIN_90_L",
"BOTH_DEATH_SPIN_180",
"BOTH_DEATH_LYING_UP",
"BOTH_DEATH_LYING_DN",
"BOTH_DEATH_FALLING_DN",
"BOTH_DEATH_FALLING_UP",
"BOTH_DEATH_CROUCHED",
"BOTH_DEAD1",
"BOTH_DEAD2",
"BOTH_DEAD3",
"BOTH_DEAD4",
"BOTH_DEAD5",
"BOTH_DEAD6",
"BOTH_DEAD7",
"BOTH_DEAD8",
"BOTH_DEAD9",
"BOTH_DEAD10",
"BOTH_DEAD11",
"BOTH_DEAD12",
"BOTH_DEAD13",
"BOTH_DEAD14",
"BOTH_DEAD15",
"BOTH_DEAD16",
"BOTH_DEAD17",
"BOTH_DEAD18",
"BOTH_DEAD19",
"BOTH_DEAD20",
"BOTH_DEAD21",
"BOTH_DEAD22",
"BOTH_DEAD23",
"BOTH_DEAD24",
"BOTH_DEAD25",
"BOTH_DEADFORWARD1",
"BOTH_DEADFORWARD2",
"BOTH_DEADBACKWARD1",
"BOTH_DEADBACKWARD2",
"BOTH_LYINGDEAD1",
"BOTH_STUMBLEDEAD1",
"BOTH_FALLDEAD1LAND",
"BOTH_DEADFLOP1",
"BOTH_DEADFLOP2",
"BOTH_DISMEMBER_HEAD1",
"BOTH_DISMEMBER_TORSO1",
"BOTH_DISMEMBER_LLEG",
"BOTH_DISMEMBER_RLEG",
"BOTH_DISMEMBER_RARM",
"BOTH_DISMEMBER_LARM",
"BOTH_PAIN1",
"BOTH_PAIN2",
"BOTH_PAIN3",
"BOTH_PAIN4",
"BOTH_PAIN5",
"BOTH_PAIN6",
"BOTH_PAIN7",
"BOTH_PAIN8",
"BOTH_PAIN9",
"BOTH_PAIN10",
"BOTH_PAIN11",
"BOTH_PAIN12",
"BOTH_PAIN13",
"BOTH_PAIN14",
"BOTH_PAIN15",
"BOTH_PAIN16",
"BOTH_PAIN17",
"BOTH_PAIN18",
"BOTH_ATTACK1",
"BOTH_ATTACK2",
"BOTH_ATTACK3",
"BOTH_ATTACK4",
"BOTH_ATTACK5",
"BOTH_ATTACK6",
"BOTH_ATTACK7",
"BOTH_ATTACK10",
"BOTH_ATTACK11",
"BOTH_MELEE1",
"BOTH_MELEE2",
"BOTH_THERMAL_READY",
"BOTH_THERMAL_THROW",
"BOTH_A1_T__B_",
"BOTH_A1__L__R",
"BOTH_A1__R__L",
"BOTH_A1_TL_BR",
"BOTH_A1_BR_TL",
"BOTH_A1_BL_TR",
"BOTH_A1_TR_BL",
"BOTH_T1_BR__R",
"BOTH_T1_BR_TL",
"BOTH_T1_BR__L",
"BOTH_T1_BR_BL",
"BOTH_T1__R_TR",
"BOTH_T1__R_TL",
"BOTH_T1__R__L",
"BOTH_T1__R_BL",
"BOTH_T1_TR_BR",
"BOTH_T1_TR_TL",
"BOTH_T1_TR__L",
"BOTH_T1_TR_BL",
"BOTH_T1_T__BR",
"BOTH_T1_T___R",
"BOTH_T1_T__TR",
"BOTH_T1_T__TL",
"BOTH_T1_T___L",
"BOTH_T1_T__BL",
"BOTH_T1_TL_BR",
"BOTH_T1_TL_BL",
"BOTH_T1__L_BR",
"BOTH_T1__L__R",
"BOTH_T1__L_TL",
"BOTH_T1_BL_BR",
"BOTH_T1_BL__R",
"BOTH_T1_BL_TR",
"BOTH_T1_BL__L",
"BOTH_T1_BR_TR",
"BOTH_T1_BR_T_",
"BOTH_T1__R_BR",
"BOTH_T1__R_T_",
"BOTH_T1_TR__R",
"BOTH_T1_TR_T_",
"BOTH_T1_TL__R",
"BOTH_T1_TL_TR",
"BOTH_T1_TL_T_",
"BOTH_T1_TL__L",
"BOTH_T1__L_TR",
"BOTH_T1__L_T_",
"BOTH_T1__L_BL",
"BOTH_T1_BL_T_",
"BOTH_T1_BL_TL",
"BOTH_S1_S1_T_",
"BOTH_S1_S1__L",
"BOTH_S1_S1__R",
"BOTH_S1_S1_TL",
"BOTH_S1_S1_BR",
"BOTH_S1_S1_BL",
"BOTH_S1_S1_TR",
"BOTH_R1_B__S1",
"BOTH_R1__L_S1",
"BOTH_R1__R_S1",
"BOTH_R1_TL_S1",
"BOTH_R1_BR_S1",
"BOTH_R1_BL_S1",
"BOTH_R1_TR_S1",
"BOTH_B1_BR___",
"BOTH_B1__R___",
"BOTH_B1_TR___",
"BOTH_B1_T____",
"BOTH_B1_TL___",
"BOTH_B1__L___",
"BOTH_B1_BL___",
"BOTH_D1_BR___",
"BOTH_D1__R___",
"BOTH_D1_TR___",
"BOTH_D1_TL___",
"BOTH_D1__L___",
"BOTH_D1_BL___",
"BOTH_D1_B____",
"BOTH_A2_T__B_",
"BOTH_A2__L__R",
"BOTH_A2__R__L",
"BOTH_A2_TL_BR",
"BOTH_A2_BR_TL",
"BOTH_A2_BL_TR",
"BOTH_A2_TR_BL",
"BOTH_T2_BR__R",
"BOTH_T2_BR_TL",
"BOTH_T2_BR__L",
"BOTH_T2_BR_BL",
"BOTH_T2__R_TR",
"BOTH_T2__R_TL",
"BOTH_T2__R__L",
"BOTH_T2__R_BL",
"BOTH_T2_TR_BR",
"BOTH_T2_TR_TL",
"BOTH_T2_TR__L",
"BOTH_T2_TR_BL",
"BOTH_T2_T__BR",
"BOTH_T2_T___R",
"BOTH_T2_T__TR",
"BOTH_T2_T__TL",
"BOTH_T2_T___L",
"BOTH_T2_T__BL",
"BOTH_T2_TL_BR",
"BOTH_T2_TL_BL",
"BOTH_T2__L_BR",
"BOTH_T2__L__R",
"BOTH_T2__L_TL",
"BOTH_T2_BL_BR",
"BOTH_T2_BL__R",
"BOTH_T2_BL_TR",
"BOTH_T2_BL__L",
"BOTH_T2_BR_TR",
"BOTH_T2_BR_T_",
"BOTH_T2__R_BR",
"BOTH_T2__R_T_",
"BOTH_T2_TR__R",
"BOTH_T2_TR_T_",
"BOTH_T2_TL__R",
"BOTH_T2_TL_TR",
"BOTH_T2_TL_T_",
"BOTH_T2_TL__L",
"BOTH_T2__L_TR",
"BOTH_T2__L_T_",
"BOTH_T2__L_BL",
"BOTH_T2_BL_T_",
"BOTH_T2_BL_TL",
"BOTH_S2_S1_T_",
"BOTH_S2_S1__L",
"BOTH_S2_S1__R",
"BOTH_S2_S1_TL",
"BOTH_S2_S1_BR",
"BOTH_S2_S1_BL",
"BOTH_S2_S1_TR",
"BOTH_R2_B__S1",
"BOTH_R2__L_S1",
"BOTH_R2__R_S1",
"BOTH_R2_TL_S1",
"BOTH_R2_BR_S1",
"BOTH_R2_BL_S1",
"BOTH_R2_TR_S1",
"BOTH_B2_BR___",
"BOTH_B2__R___",
"BOTH_B2_TR___",
"BOTH_B2_T____",
"BOTH_B2_TL___",
"BOTH_B2__L___",
"BOTH_B2_BL___",
"BOTH_D2_BR___",
"BOTH_D2__R___",
"BOTH_D2_TR___",
"BOTH_D2_TL___",
"BOTH_D2__L___",
"BOTH_D2_BL___",
"BOTH_D2_B____",
"BOTH_A3_T__B_",
"BOTH_A3__L__R",
"BOTH_A3__R__L",
"BOTH_A3_TL_BR",
"BOTH_A3_BR_TL",
"BOTH_A3_BL_TR",
"BOTH_A3_TR_BL",
"BOTH_T3_BR__R",
"BOTH_T3_BR_TL",
"BOTH_T3_BR__L",
"BOTH_T3_BR_BL",
"BOTH_T3__R_TR",
"BOTH_T3__R_TL",
"BOTH_T3__R__L",
"BOTH_T3__R_BL",
"BOTH_T3_TR_BR",
"BOTH_T3_TR_TL",
"BOTH_T3_TR__L",
"BOTH_T3_TR_BL",
"BOTH_T3_T__BR",
"BOTH_T3_T___R",
"BOTH_T3_T__TR",
"BOTH_T3_T__TL",
"BOTH_T3_T___L",
"BOTH_T3_T__BL",
"BOTH_T3_TL_BR",
"BOTH_T3_TL_BL",
"BOTH_T3__L_BR",
"BOTH_T3__L__R",
"BOTH_T3__L_TL",
"BOTH_T3_BL_BR",
"BOTH_T3_BL__R",
"BOTH_T3_BL_TR",
"BOTH_T3_BL__L",
"BOTH_T3_BR_TR",
"BOTH_T3_BR_T_",
"BOTH_T3__R_BR",
"BOTH_T3__R_T_",
"BOTH_T3_TR__R",
"BOTH_T3_TR_T_",
"BOTH_T3_TL__R",
"BOTH_T3_TL_TR",
"BOTH_T3_TL_T_",
"BOTH_T3_TL__L",
"BOTH_T3__L_TR",
"BOTH_T3__L_T_",
"BOTH_T3__L_BL",
"BOTH_T3_BL_T_",
"BOTH_T3_BL_TL",
"BOTH_S3_S1_T_",
"BOTH_S3_S1__L",
"BOTH_S3_S1__R",
"BOTH_S3_S1_TL",
"BOTH_S3_S1_BR",
"BOTH_S3_S1_BL",
"BOTH_S3_S1_TR",
"BOTH_R3_B__S1",
"BOTH_R3__L_S1",
"BOTH_R3__R_S1",
"BOTH_R3_TL_S1",
"BOTH_R3_BR_S1",
"BOTH_R3_BL_S1",
"BOTH_R3_TR_S1",
"BOTH_B3_BR___",
"BOTH_B3__R___",
"BOTH_B3_TR___",
"BOTH_B3_T____",
"BOTH_B3_TL___",
"BOTH_B3__L___",
"BOTH_B3_BL___",
"BOTH_D3_BR___",
"BOTH_D3__R___",
"BOTH_D3_TR___",
"BOTH_D3_TL___",
"BOTH_D3__L___",
"BOTH_D3_BL___",
"BOTH_D3_B____",
"BOTH_A4_T__B_",
"BOTH_A4__L__R",
"BOTH_A4__R__L",
"BOTH_A4_TL_BR",
"BOTH_A4_BR_TL",
"BOTH_A4_BL_TR",
"BOTH_A4_TR_BL",
"BOTH_T4_BR__R",
"BOTH_T4_BR_TL",
"BOTH_T4_BR__L",
"BOTH_T4_BR_BL",
"BOTH_T4__R_TR",
"BOTH_T4__R_TL",
"BOTH_T4__R__L",
"BOTH_T4__R_BL",
"BOTH_T4_TR_BR",
"BOTH_T4_TR_TL",
"BOTH_T4_TR__L",
"BOTH_T4_TR_BL",
"BOTH_T4_T__BR",
"BOTH_T4_T___R",
"BOTH_T4_T__TR",
"BOTH_T4_T__TL",
"BOTH_T4_T___L",
"BOTH_T4_T__BL",
"BOTH_T4_TL_BR",
"BOTH_T4_TL_BL",
"BOTH_T4__L_BR",
"BOTH_T4__L__R",
"BOTH_T4__L_TL",
"BOTH_T4_BL_BR",
"BOTH_T4_BL__R",
"BOTH_T4_BL_TR",
"BOTH_T4_BL__L",
"BOTH_T4_BR_TR",
"BOTH_T4_BR_T_",
"BOTH_T4__R_BR",
"BOTH_T4__R_T_",
"BOTH_T4_TR__R",
"BOTH_T4_TR_T_",
"BOTH_T4_TL__R",
"BOTH_T4_TL_TR",
"BOTH_T4_TL_T_",
"BOTH_T4_TL__L",
"BOTH_T4__L_TR",
"BOTH_T4__L_T_",
"BOTH_T4__L_BL",
"BOTH_T4_BL_T_",
"BOTH_T4_BL_TL",
"BOTH_S4_S1_T_",
"BOTH_S4_S1__L",
"BOTH_S4_S1__R",
"BOTH_S4_S1_TL",
"BOTH_S4_S1_BR",
"BOTH_S4_S1_BL",
"BOTH_S4_S1_TR",
"BOTH_R4_B__S1",
"BOTH_R4__L_S1",
"BOTH_R4__R_S1",
"BOTH_R4_TL_S1",
"BOTH_R4_BR_S1",
"BOTH_R4_BL_S1",
"BOTH_R4_TR_S1",
"BOTH_B4_BR___",
"BOTH_B4__R___",
"BOTH_B4_TR___",
"BOTH_B4_T____",
"BOTH_B4_TL___",
"BOTH_B4__L___",
"BOTH_B4_BL___",
"BOTH_D4_BR___",
"BOTH_D4__R___",
"BOTH_D4_TR___",
"BOTH_D4_TL___",
"BOTH_D4__L___",
"BOTH_D4_BL___",
"BOTH_D4_B____",
"BOTH_A5_T__B_",
"BOTH_A5__L__R",
"BOTH_A5__R__L",
"BOTH_A5_TL_BR",
"BOTH_A5_BR_TL",
"BOTH_A5_BL_TR",
"BOTH_A5_TR_BL",
"BOTH_T5_BR__R",
"BOTH_T5_BR_TL",
"BOTH_T5_BR__L",
"BOTH_T5_BR_BL",
"BOTH_T5__R_TR",
"BOTH_T5__R_TL",
"BOTH_T5__R__L",
"BOTH_T5__R_BL",
"BOTH_T5_TR_BR",
"BOTH_T5_TR_TL",
"BOTH_T5_TR__L",
"BOTH_T5_TR_BL",
"BOTH_T5_T__BR",
"BOTH_T5_T___R",
"BOTH_T5_T__TR",
"BOTH_T5_T__TL",
"BOTH_T5_T___L",
"BOTH_T5_T__BL",
"BOTH_T5_TL_BR",
"BOTH_T5_TL_BL",
"BOTH_T5__L_BR",
"BOTH_T5__L__R",
"BOTH_T5__L_TL",
"BOTH_T5_BL_BR",
"BOTH_T5_BL__R",
"BOTH_T5_BL_TR",
"BOTH_T5_BL__L",
"BOTH_T5_BR_TR",
"BOTH_T5_BR_T_",
"BOTH_T5__R_BR",
"BOTH_T5__R_T_",
"BOTH_T5_TR__R",
"BOTH_T5_TR_T_",
"BOTH_T5_TL__R",
"BOTH_T5_TL_TR",
"BOTH_T5_TL_T_",
"BOTH_T5_TL__L",
"BOTH_T5__L_TR",
"BOTH_T5__L_T_",
"BOTH_T5__L_BL",
"BOTH_T5_BL_T_",
"BOTH_T5_BL_TL",
"BOTH_S5_S1_T_",
"BOTH_S5_S1__L",
"BOTH_S5_S1__R",
"BOTH_S5_S1_TL",
"BOTH_S5_S1_BR",
"BOTH_S5_S1_BL",
"BOTH_S5_S1_TR",
"BOTH_R5_B__S1",
"BOTH_R5__L_S1",
"BOTH_R5__R_S1",
"BOTH_R5_TL_S1",
"BOTH_R5_BR_S1",
"BOTH_R5_BL_S1",
"BOTH_R5_TR_S1",
"BOTH_B5_BR___",
"BOTH_B5__R___",
"BOTH_B5_TR___",
"BOTH_B5_T____",
"BOTH_B5_TL___",
"BOTH_B5__L___",
"BOTH_B5_BL___",
"BOTH_D5_BR___",
"BOTH_D5__R___",
"BOTH_D5_TR___",
"BOTH_D5_TL___",
"BOTH_D5__L___",
"BOTH_D5_BL___",
"BOTH_D5_B____",
"BOTH_A6_T__B_",
"BOTH_A6__L__R",
"BOTH_A6__R__L",
"BOTH_A6_TL_BR",
"BOTH_A6_BR_TL",
"BOTH_A6_BL_TR",
"BOTH_A6_TR_BL",
"BOTH_T6_BR__R",
"BOTH_T6_BR_TL",
"BOTH_T6_BR__L",
"BOTH_T6_BR_BL",
"BOTH_T6__R_TR",
"BOTH_T6__R_TL",
"BOTH_T6__R__L",
"BOTH_T6__R_BL",
"BOTH_T6_TR_BR",
"BOTH_T6_TR_TL",
"BOTH_T6_TR__L",
"BOTH_T6_TR_BL",
"BOTH_T6_T__BR",
"BOTH_T6_T___R",
"BOTH_T6_T__TR",
"BOTH_T6_T__TL",
"BOTH_T6_T___L",
"BOTH_T6_T__BL",
"BOTH_T6_TL_BR",
"BOTH_T6_TL_BL",
"BOTH_T6__L_BR",
"BOTH_T6__L__R",
"BOTH_T6__L_TL",
"BOTH_T6_BL_BR",
"BOTH_T6_BL__R",
"BOTH_T6_BL_TR",
"BOTH_T6_BL__L",
"BOTH_T6_BR_TR",
"BOTH_T6_BR_T_",
"BOTH_T6__R_BR",
"BOTH_T6__R_T_",
"BOTH_T6_TR__R",
"BOTH_T6_TR_T_",
"BOTH_T6_TL__R",
"BOTH_T6_TL_TR",
"BOTH_T6_TL_T_",
"BOTH_T6_TL__L",
"BOTH_T6__L_TR",
"BOTH_T6__L_T_",
"BOTH_T6__L_BL",
"BOTH_T6_BL_T_",
"BOTH_T6_BL_TL",
"BOTH_S6_S6_T_",
"BOTH_S6_S6__L",
"BOTH_S6_S6__R",
"BOTH_S6_S6_TL",
"BOTH_S6_S6_BR",
"BOTH_S6_S6_BL",
"BOTH_S6_S6_TR",
"BOTH_R6_B__S6",
"BOTH_R6__L_S6",
"BOTH_R6__R_S6",
"BOTH_R6_TL_S6",
"BOTH_R6_BR_S6",
"BOTH_R6_BL_S6",
"BOTH_R6_TR_S6",
"BOTH_B6_BR___",
"BOTH_B6__R___",
"BOTH_B6_TR___",
"BOTH_B6_T____",
"BOTH_B6_TL___",
"BOTH_B6__L___",
"BOTH_B6_BL___",
"BOTH_D6_BR___",
"BOTH_D6__R___",
"BOTH_D6_TR___",
"BOTH_D6_TL___",
"BOTH_D6__L___",
"BOTH_D6_BL___",
"BOTH_D6_B____",
"BOTH_A7_T__B_",
"BOTH_A7__L__R",
"BOTH_A7__R__L",
"BOTH_A7_TL_BR",
"BOTH_A7_BR_TL",
"BOTH_A7_BL_TR",
"BOTH_A7_TR_BL",
"BOTH_T7_BR__R",
"BOTH_T7_BR_TL",
"BOTH_T7_BR__L",
"BOTH_T7_BR_BL",
"BOTH_T7__R_TR",
"BOTH_T7__R_TL",
"BOTH_T7__R__L",
"BOTH_T7__R_BL",
"BOTH_T7_TR_BR",
"BOTH_T7_TR_TL",
"BOTH_T7_TR__L",
"BOTH_T7_TR_BL",
"BOTH_T7_T__BR",
"BOTH_T7_T___R",
"BOTH_T7_T__TR",
"BOTH_T7_T__TL",
"BOTH_T7_T___L",
"BOTH_T7_T__BL",
"BOTH_T7_TL_BR",
"BOTH_T7_TL_BL",
"BOTH_T7__L_BR",
"BOTH_T7__L__R",
"BOTH_T7__L_TL",
"BOTH_T7_BL_BR",
"BOTH_T7_BL__R",
"BOTH_T7_BL_TR",
"BOTH_T7_BL__L",
"BOTH_T7_BR_TR",
"BOTH_T7_BR_T_",
"BOTH_T7__R_BR",
"BOTH_T7__R_T_",
"BOTH_T7_TR__R",
"BOTH_T7_TR_T_",
"BOTH_T7_TL__R",
"BOTH_T7_TL_TR",
"BOTH_T7_TL_T_",
"BOTH_T7_TL__L",
"BOTH_T7__L_TR",
"BOTH_T7__L_T_",
"BOTH_T7__L_BL",
"BOTH_T7_BL_T_",
"BOTH_T7_BL_TL",
"BOTH_S7_S7_T_",
"BOTH_S7_S7__L",
"BOTH_S7_S7__R",
"BOTH_S7_S7_TL",
"BOTH_S7_S7_BR",
"BOTH_S7_S7_BL",
"BOTH_S7_S7_TR",
"BOTH_R7_B__S7",
"BOTH_R7__L_S7",
"BOTH_R7__R_S7",
"BOTH_R7_TL_S7",
"BOTH_R7_BR_S7",
"BOTH_R7_BL_S7",
"BOTH_R7_TR_S7",
"BOTH_B7_BR___",
"BOTH_B7__R___",
"BOTH_B7_TR___",
"BOTH_B7_T____",
"BOTH_B7_TL___",
"BOTH_B7__L___",
"BOTH_B7_BL___",
"BOTH_D7_BR___",
"BOTH_D7__R___",
"BOTH_D7_TR___",
"BOTH_D7_TL___",
"BOTH_D7__L___",
"BOTH_D7_BL___",
"BOTH_D7_B____",
"BOTH_P1_S1_T_",
"BOTH_P1_S1_TR",
"BOTH_P1_S1_TL",
"BOTH_P1_S1_BL",
"BOTH_P1_S1_BR",
"BOTH_K1_S1_T_",
"BOTH_K1_S1_TR",
"BOTH_K1_S1_TL",
"BOTH_K1_S1_BL",
"BOTH_K1_S1_B_",
"BOTH_K1_S1_BR",
"BOTH_V1_BR_S1",
"BOTH_V1__R_S1",
"BOTH_V1_TR_S1",
"BOTH_V1_T__S1",
"BOTH_V1_TL_S1",
"BOTH_V1__L_S1",
"BOTH_V1_BL_S1",
"BOTH_V1_B__S1",
"BOTH_H1_S1_T_",
"BOTH_H1_S1_TR",
"BOTH_H1_S1_TL",
"BOTH_H1_S1_BL",
"BOTH_H1_S1_B_",
"BOTH_H1_S1_BR",
"BOTH_P6_S6_T_",
"BOTH_P6_S6_TR",
"BOTH_P6_S6_TL",
"BOTH_P6_S6_BL",
"BOTH_P6_S6_BR",
"BOTH_K6_S6_T_",
"BOTH_K6_S6_TR",
"BOTH_K6_S6_TL",
"BOTH_K6_S6_BL",
"BOTH_K6_S6_B_",
"BOTH_K6_S6_BR",
"BOTH_V6_BR_S6",
"BOTH_V6__R_S6",
"BOTH_V6_TR_S6",
"BOTH_V6_T__S6",
"BOTH_V6_TL_S6",
"BOTH_V6__L_S6",
"BOTH_V6_BL_S6",
"BOTH_V6_B__S6",
"BOTH_H6_S6_T_",
"BOTH_H6_S6_TR",
"BOTH_H6_S6_TL",
"BOTH_H6_S6_BL",
"BOTH_H6_S6_B_",
"BOTH_H6_S6_BR",
"BOTH_P7_S7_T_",
"BOTH_P7_S7_TR",
"BOTH_P7_S7_TL",
"BOTH_P7_S7_BL",
"BOTH_P7_S7_BR",
"BOTH_K7_S7_T_",
"BOTH_K7_S7_TR",
"BOTH_K7_S7_TL",
"BOTH_K7_S7_BL",
"BOTH_K7_S7_B_",
"BOTH_K7_S7_BR",
"BOTH_V7_BR_S7",
"BOTH_V7__R_S7",
"BOTH_V7_TR_S7",
"BOTH_V7_T__S7",
"BOTH_V7_TL_S7",
"BOTH_V7__L_S7",
"BOTH_V7_BL_S7",
"BOTH_V7_B__S7",
"BOTH_H7_S7_T_",
"BOTH_H7_S7_TR",
"BOTH_H7_S7_TL",
"BOTH_H7_S7_BL",
"BOTH_H7_S7_B_",
"BOTH_H7_S7_BR",
"BOTH_LK_S_DL_S_B_1_L",
"BOTH_LK_S_DL_S_B_1_W",
"BOTH_LK_S_DL_S_L_1",
"BOTH_LK_S_DL_S_SB_1_L",
"BOTH_LK_S_DL_S_SB_1_W",
"BOTH_LK_S_DL_T_B_1_L",
"BOTH_LK_S_DL_T_B_1_W",
"BOTH_LK_S_DL_T_L_1",
"BOTH_LK_S_DL_T_SB_1_L",
"BOTH_LK_S_DL_T_SB_1_W",
"BOTH_LK_S_ST_S_B_1_L",
"BOTH_LK_S_ST_S_B_1_W",
"BOTH_LK_S_ST_S_L_1",
"BOTH_LK_S_ST_S_SB_1_L",
"BOTH_LK_S_ST_S_SB_1_W",
"BOTH_LK_S_ST_T_B_1_L",
"BOTH_LK_S_ST_T_B_1_W",
"BOTH_LK_S_ST_T_L_1",
"BOTH_LK_S_ST_T_SB_1_L",
"BOTH_LK_S_ST_T_SB_1_W",
"BOTH_LK_S_S_S_B_1_L",
"BOTH_LK_S_S_S_B_1_W",
"BOTH_LK_S_S_S_L_1",
"BOTH_LK_S_S_S_SB_1_L",
"BOTH_LK_S_S_S_SB_1_W",
"BOTH_LK_S_S_T_B_1_L",
"BOTH_LK_S_S_T_B_1_W",
"BOTH_LK_S_S_T_L_1",
"BOTH_LK_S_S_T_SB_1_L",
"BOTH_LK_S_S_T_SB_1_W",
"BOTH_LK_DL_DL_S_B_1_L",
"BOTH_LK_DL_DL_S_B_1_W",
"BOTH_LK_DL_DL_S_L_1",
"BOTH_LK_DL_DL_S_SB_1_L",
"BOTH_LK_DL_DL_S_SB_1_W",
"BOTH_LK_DL_DL_T_B_1_L",
"BOTH_LK_DL_DL_T_B_1_W",
"BOTH_LK_DL_DL_T_L_1",
"BOTH_LK_DL_DL_T_SB_1_L",
"BOTH_LK_DL_DL_T_SB_1_W",
"BOTH_LK_DL_ST_S_B_1_L",
"BOTH_LK_DL_ST_S_B_1_W",
"BOTH_LK_DL_ST_S_L_1",
"BOTH_LK_DL_ST_S_SB_1_L",
"BOTH_LK_DL_ST_S_SB_1_W",
"BOTH_LK_DL_ST_T_B_1_L",
"BOTH_LK_DL_ST_T_B_1_W",
"BOTH_LK_DL_ST_T_L_1",
"BOTH_LK_DL_ST_T_SB_1_L",
"BOTH_LK_DL_ST_T_SB_1_W",
"BOTH_LK_DL_S_S_B_1_L",
"BOTH_LK_DL_S_S_B_1_W",
"BOTH_LK_DL_S_S_L_1",
"BOTH_LK_DL_S_S_SB_1_L",
"BOTH_LK_DL_S_S_SB_1_W",
"BOTH_LK_DL_S_T_B_1_L",
"BOTH_LK_DL_S_T_B_1_W",
"BOTH_LK_DL_S_T_L_1",
"BOTH_LK_DL_S_T_SB_1_L",
"BOTH_LK_DL_S_T_SB_1_W",
"BOTH_LK_ST_DL_S_B_1_L",
"BOTH_LK_ST_DL_S_B_1_W",
"BOTH_LK_ST_DL_S_L_1",
"BOTH_LK_ST_DL_S_SB_1_L",
"BOTH_LK_ST_DL_S_SB_1_W",
"BOTH_LK_ST_DL_T_B_1_L",
"BOTH_LK_ST_DL_T_B_1_W",
"BOTH_LK_ST_DL_T_L_1",
"BOTH_LK_ST_DL_T_SB_1_L",
"BOTH_LK_ST_DL_T_SB_1_W",
"BOTH_LK_ST_ST_S_B_1_L",
"BOTH_LK_ST_ST_S_B_1_W",
"BOTH_LK_ST_ST_S_L_1",
"BOTH_LK_ST_ST_S_SB_1_L",
"BOTH_LK_ST_ST_S_SB_1_W",
"BOTH_LK_ST_ST_T_B_1_L",
"BOTH_LK_ST_ST_T_B_1_W",
"BOTH_LK_ST_ST_T_L_1",
"BOTH_LK_ST_ST_T_SB_1_L",
"BOTH_LK_ST_ST_T_SB_1_W",
"BOTH_LK_ST_S_S_B_1_L",
"BOTH_LK_ST_S_S_B_1_W",
"BOTH_LK_ST_S_S_L_1",
"BOTH_LK_ST_S_S_SB_1_L",
"BOTH_LK_ST_S_S_SB_1_W",
"BOTH_LK_ST_S_T_B_1_L",
"BOTH_LK_ST_S_T_B_1_W",
"BOTH_LK_ST_S_T_L_1",
"BOTH_LK_ST_S_T_SB_1_L",
"BOTH_LK_ST_S_T_SB_1_W",
"BOTH_LK_S_S_S_L_2",
"BOTH_LK_S_S_T_L_2",
"BOTH_LK_DL_DL_S_L_2",
"BOTH_LK_DL_DL_T_L_2",
"BOTH_LK_ST_ST_S_L_2",
"BOTH_LK_ST_ST_T_L_2",
"BOTH_BF2RETURN",
"BOTH_BF2BREAK",
"BOTH_BF2LOCK",
"BOTH_BF1RETURN",
"BOTH_BF1BREAK",
"BOTH_BF1LOCK",
"BOTH_CWCIRCLE_R2__R_S1",
"BOTH_CCWCIRCLE_R2__L_S1",
"BOTH_CWCIRCLE_A2__L__R",
"BOTH_CCWCIRCLE_A2__R__L",
"BOTH_CWCIRCLEBREAK",
"BOTH_CCWCIRCLEBREAK",
"BOTH_CWCIRCLELOCK",
"BOTH_CCWCIRCLELOCK",
"BOTH_SABERFAST_STANCE",
"BOTH_SABERSLOW_STANCE",
"BOTH_SABERDUAL_STANCE",
"BOTH_SABERSTAFF_STANCE",
"BOTH_A2_STABBACK1",
"BOTH_ATTACK_BACK",
"BOTH_JUMPFLIPSLASHDOWN1",
"BOTH_JUMPFLIPSTABDOWN",
"BOTH_FORCELEAP2_T__B_",
"BOTH_LUNGE2_B__T_",
"BOTH_CROUCHATTACKBACK1",
"BOTH_JUMPATTACK6",
"BOTH_JUMPATTACK7",
"BOTH_SPINATTACK6",
"BOTH_SPINATTACK7",
"BOTH_S1_S6",
"BOTH_S6_S1",
"BOTH_S1_S7",
"BOTH_S7_S1",
"BOTH_FORCELONGLEAP_START",
"BOTH_FORCELONGLEAP_ATTACK",
"BOTH_FORCELONGLEAP_LAND",
"BOTH_FORCEWALLRUNFLIP_START",
"BOTH_FORCEWALLRUNFLIP_END",
"BOTH_FORCEWALLRUNFLIP_ALT",
"BOTH_FORCEWALLREBOUND_FORWARD",
"BOTH_FORCEWALLREBOUND_LEFT",
"BOTH_FORCEWALLREBOUND_BACK",
"BOTH_FORCEWALLREBOUND_RIGHT",
"BOTH_FORCEWALLHOLD_FORWARD",
"BOTH_FORCEWALLHOLD_LEFT",
"BOTH_FORCEWALLHOLD_BACK",
"BOTH_FORCEWALLHOLD_RIGHT",
"BOTH_FORCEWALLRELEASE_FORWARD",
"BOTH_FORCEWALLRELEASE_LEFT",
"BOTH_FORCEWALLRELEASE_BACK",
"BOTH_FORCEWALLRELEASE_RIGHT",
"BOTH_A7_KICK_F",
"BOTH_A7_KICK_B",
"BOTH_A7_KICK_R",
"BOTH_A7_KICK_L",
"BOTH_A7_KICK_S",
"BOTH_A7_KICK_BF",
"BOTH_A7_KICK_BF_STOP",
"BOTH_A7_KICK_RL",
"BOTH_A7_KICK_F_AIR",
"BOTH_A7_KICK_B_AIR",
"BOTH_A7_KICK_R_AIR",
"BOTH_A7_KICK_L_AIR",
"BOTH_FLIP_ATTACK7",
"BOTH_FLIP_HOLD7",
"BOTH_FLIP_LAND",
"BOTH_PULL_IMPALE_STAB",
"BOTH_PULL_IMPALE_SWING",
"BOTH_PULLED_INAIR_B",
"BOTH_PULLED_INAIR_F",
"BOTH_STABDOWN",
"BOTH_STABDOWN_STAFF",
"BOTH_STABDOWN_DUAL",
"BOTH_A6_SABERPROTECT",
"BOTH_A7_SOULCAL",
"BOTH_A1_SPECIAL",
"BOTH_A2_SPECIAL",
"BOTH_A3_SPECIAL",
"BOTH_ROLL_STAB",
"BOTH_STAND1",
"BOTH_STAND1IDLE1",
"BOTH_STAND2",
"BOTH_STAND2IDLE1",
"BOTH_STAND2IDLE2",
"BOTH_STAND3",
"BOTH_STAND3IDLE1",
"BOTH_STAND4",
"BOTH_STAND5",
"BOTH_STAND5IDLE1",
"BOTH_STAND6",
"BOTH_STAND8",
"BOTH_STAND1TO2",
"BOTH_STAND2TO1",
"BOTH_STAND2TO4",
"BOTH_STAND4TO2",
"BOTH_STAND4TOATTACK2",
"BOTH_STANDUP2",
"BOTH_STAND5TOSIT3",
"BOTH_STAND1TOSTAND5",
"BOTH_STAND5TOSTAND1",
"BOTH_STAND5TOAIM",
"BOTH_STAND5STARTLEDLOOKLEFT",
"BOTH_STARTLEDLOOKLEFTTOSTAND5",
"BOTH_STAND5TOSTAND8",
"BOTH_STAND7TOSTAND8",
"BOTH_STAND8TOSTAND5",
"BOTH_STAND9",
"BOTH_STAND9IDLE1",
"BOTH_STAND5SHIFTWEIGHT",
"BOTH_STAND5SHIFTWEIGHTSTART",
"BOTH_STAND5SHIFTWEIGHTSTOP",
"BOTH_STAND5TURNLEFTSTART",
"BOTH_STAND5TURNLEFTSTOP",
"BOTH_STAND5TURNRIGHTSTART",
"BOTH_STAND5TURNRIGHTSTOP",
"BOTH_STAND5LOOK180LEFTSTART",
"BOTH_STAND5LOOK180LEFTSTOP",
"BOTH_CONSOLE1START",
"BOTH_CONSOLE1",
"BOTH_CONSOLE1STOP",
"BOTH_CONSOLE2START",
"BOTH_CONSOLE2",
"BOTH_CONSOLE2STOP",
"BOTH_CONSOLE2HOLDCOMSTART",
"BOTH_CONSOLE2HOLDCOMSTOP",
"BOTH_GUARD_LOOKAROUND1",
"BOTH_GUARD_IDLE1",
"BOTH_GESTURE1",
"BOTH_GESTURE2",
"BOTH_WALK1TALKCOMM1",
"BOTH_TALK1",
"BOTH_TALK2",
"BOTH_TALKCOMM1START",
"BOTH_TALKCOMM1",
"BOTH_TALKCOMM1STOP",
"BOTH_TALKGESTURE1",
"BOTH_HEADTILTLSTART",
"BOTH_HEADTILTLSTOP",
"BOTH_HEADTILTRSTART",
"BOTH_HEADTILTRSTOP",
"BOTH_HEADNOD",
"BOTH_HEADSHAKE",
"BOTH_SIT2HEADTILTLSTART",
"BOTH_SIT2HEADTILTLSTOP",
"BOTH_REACH1START",
"BOTH_REACH1STOP",
"BOTH_COME_ON1",
"BOTH_STEADYSELF1",
"BOTH_STEADYSELF1END",
"BOTH_SILENCEGESTURE1",
"BOTH_REACHFORSABER1",
"BOTH_SABERKILLER1",
"BOTH_SABERKILLEE1",
"BOTH_HUGGER1",
"BOTH_HUGGERSTOP1",
"BOTH_HUGGEE1",
"BOTH_HUGGEESTOP1",
"BOTH_SABERTHROW1START",
"BOTH_SABERTHROW1STOP",
"BOTH_SABERTHROW2START",
"BOTH_SABERTHROW2STOP",
"BOTH_SIT1",
"BOTH_SIT2",
"BOTH_SIT3",
"BOTH_SIT2TOSTAND5",
"BOTH_STAND5TOSIT2",
"BOTH_SIT2TOSIT4",
"BOTH_SIT3TOSTAND5",
"BOTH_CROUCH1",
"BOTH_CROUCH1IDLE",
"BOTH_CROUCH1WALK",
"BOTH_CROUCH1WALKBACK",
"BOTH_UNCROUCH1",
"BOTH_CROUCH2TOSTAND1",
"BOTH_CROUCH3",
"BOTH_UNCROUCH3",
"BOTH_CROUCH4",
"BOTH_UNCROUCH4",
"BOTH_GUNSIT1",
"BOTH_VS_MOUNT_L",
"BOTH_VS_DISMOUNT_L",
"BOTH_VS_MOUNT_R",
"BOTH_VS_DISMOUNT_R",
"BOTH_VS_MOUNTJUMP_L",
"BOTH_VS_MOUNTTHROW",
"BOTH_VS_MOUNTTHROW_L",
"BOTH_VS_MOUNTTHROW_R",
"BOTH_VS_MOUNTTHROWEE",
"BOTH_VS_LOOKLEFT",
"BOTH_VS_LOOKRIGHT",
"BOTH_VS_TURBO",
"BOTH_VS_REV",
"BOTH_VS_AIR",
"BOTH_VS_AIR_G",
"BOTH_VS_AIR_SL",
"BOTH_VS_AIR_SR",
"BOTH_VS_LAND",
"BOTH_VS_LAND_G",
"BOTH_VS_LAND_SL",
"BOTH_VS_LAND_SR",
"BOTH_VS_IDLE",
"BOTH_VS_IDLE_G",
"BOTH_VS_IDLE_SL",
"BOTH_VS_IDLE_SR",
"BOTH_VS_LEANL",
"BOTH_VS_LEANL_G",
"BOTH_VS_LEANL_SL",
"BOTH_VS_LEANL_SR",
"BOTH_VS_LEANR",
"BOTH_VS_LEANR_G",
"BOTH_VS_LEANR_SL",
"BOTH_VS_LEANR_SR",
"BOTH_VS_ATL_S",
"BOTH_VS_ATR_S",
"BOTH_VS_ATR_TO_L_S",
"BOTH_VS_ATL_TO_R_S",
"BOTH_VS_ATR_G",
"BOTH_VS_ATL_G",
"BOTH_VS_ATF_G",
"BOTH_VS_PAIN1",
"BOTH_VT_MOUNT_L",
"BOTH_VT_MOUNT_R",
"BOTH_VT_MOUNT_B",
"BOTH_VT_DISMOUNT",
"BOTH_VT_DISMOUNT_L",
"BOTH_VT_DISMOUNT_R",
"BOTH_VT_WALK_FWD",
"BOTH_VT_WALK_REV",
"BOTH_VT_WALK_FWD_L",
"BOTH_VT_WALK_FWD_R",
"BOTH_VT_RUN_FWD",
"BOTH_VT_RUN_REV",
"BOTH_VT_RUN_FWD_L",
"BOTH_VT_RUN_FWD_R",
"BOTH_VT_SLIDEF",
"BOTH_VT_AIR",
"BOTH_VT_ATB",
"BOTH_VT_PAIN1",
"BOTH_VT_DEATH1",
"BOTH_VT_STAND",
"BOTH_VT_BUCK",
"BOTH_VT_LAND",
"BOTH_VT_TURBO",
"BOTH_VT_IDLE_SL",
"BOTH_VT_IDLE_SR",
"BOTH_VT_IDLE",
"BOTH_VT_IDLE1",
"BOTH_VT_IDLE_S",
"BOTH_VT_IDLE_G",
"BOTH_VT_IDLE_T",
"BOTH_VT_ATL_S",
"BOTH_VT_ATR_S",
"BOTH_VT_ATR_TO_L_S",
"BOTH_VT_ATL_TO_R_S",
"BOTH_VT_ATR_G",
"BOTH_VT_ATL_G",
"BOTH_VT_ATF_G",
"BOTH_GEARS_OPEN",
"BOTH_GEARS_CLOSE",
"BOTH_WINGS_OPEN",
"BOTH_WINGS_CLOSE",
"BOTH_DEATH14_UNGRIP",
"BOTH_DEATH14_SITUP",
"BOTH_KNEES1",
"BOTH_KNEES2",
"BOTH_KNEES2TO1",
"BOTH_WALK1",
"BOTH_WALK2",
"BOTH_WALK_STAFF",
"BOTH_WALKBACK_STAFF",
"BOTH_WALK_DUAL",
"BOTH_WALKBACK_DUAL",
"BOTH_WALK5",
"BOTH_WALK6",
"BOTH_WALK7",
"BOTH_RUN1",
"BOTH_RUN1START",
"BOTH_RUN1STOP",
"BOTH_RUN2",
"BOTH_RUN1TORUN2",
"BOTH_RUN2TORUN1",
"BOTH_RUN4",
"BOTH_RUN_STAFF",
"BOTH_RUNBACK_STAFF",
"BOTH_RUN_DUAL",
"BOTH_RUNBACK_DUAL",
"BOTH_STRAFE_LEFT1",
"BOTH_STRAFE_RIGHT1",
"BOTH_RUNSTRAFE_LEFT1",
"BOTH_RUNSTRAFE_RIGHT1",
"BOTH_TURN_LEFT1",
"BOTH_TURN_RIGHT1",
"BOTH_TURNSTAND1",
"BOTH_TURNSTAND2",
"BOTH_TURNSTAND3",
"BOTH_TURNSTAND4",
"BOTH_TURNSTAND5",
"BOTH_TURNCROUCH1",
"BOTH_WALKBACK1",
"BOTH_WALKBACK2",
"BOTH_RUNBACK1",
"BOTH_RUNBACK2",
"BOTH_JUMP1",
"BOTH_INAIR1",
"BOTH_LAND1",
"BOTH_LAND2",
"BOTH_JUMPBACK1",
"BOTH_INAIRBACK1",
"BOTH_LANDBACK1",
"BOTH_JUMPLEFT1",
"BOTH_INAIRLEFT1",
"BOTH_LANDLEFT1",
"BOTH_JUMPRIGHT1",
"BOTH_INAIRRIGHT1",
"BOTH_LANDRIGHT1",
"BOTH_FORCEJUMP1",
"BOTH_FORCEINAIR1",
"BOTH_FORCELAND1",
"BOTH_FORCEJUMPBACK1",
"BOTH_FORCEINAIRBACK1",
"BOTH_FORCELANDBACK1",
"BOTH_FORCEJUMPLEFT1",
"BOTH_FORCEINAIRLEFT1",
"BOTH_FORCELANDLEFT1",
"BOTH_FORCEJUMPRIGHT1",
"BOTH_FORCEINAIRRIGHT1",
"BOTH_FORCELANDRIGHT1",
"BOTH_FLIP_F",
"BOTH_FLIP_B",
"BOTH_FLIP_L",
"BOTH_FLIP_R",
"BOTH_ROLL_F",
"BOTH_ROLL_B",
"BOTH_ROLL_L",
"BOTH_ROLL_R",
"BOTH_HOP_F",
"BOTH_HOP_B",
"BOTH_HOP_L",
"BOTH_HOP_R",
"BOTH_DODGE_FL",
"BOTH_DODGE_FR",
"BOTH_DODGE_BL",
"BOTH_DODGE_BR",
"BOTH_DODGE_L",
"BOTH_DODGE_R",
"BOTH_DODGE_HOLD_FL",
"BOTH_DODGE_HOLD_FR",
"BOTH_DODGE_HOLD_BL",
"BOTH_DODGE_HOLD_BR",
"BOTH_DODGE_HOLD_L",
"BOTH_DODGE_HOLD_R",
"BOTH_ENGAGETAUNT",
"BOTH_BOW",
"BOTH_MEDITATE",
"BOTH_MEDITATE_END",
"BOTH_SHOWOFF_FAST",
"BOTH_SHOWOFF_MEDIUM",
"BOTH_SHOWOFF_STRONG",
"BOTH_SHOWOFF_DUAL",
"BOTH_SHOWOFF_STAFF",
"BOTH_VICTORY_FAST",
"BOTH_VICTORY_MEDIUM",
"BOTH_VICTORY_STRONG",
"BOTH_VICTORY_DUAL",
"BOTH_VICTORY_STAFF",
"BOTH_ARIAL_LEFT",
"BOTH_ARIAL_RIGHT",
"BOTH_CARTWHEEL_LEFT",
"BOTH_CARTWHEEL_RIGHT",
"BOTH_FLIP_LEFT",
"BOTH_FLIP_BACK1",
"BOTH_FLIP_BACK2",
"BOTH_FLIP_BACK3",
"BOTH_BUTTERFLY_LEFT",
"BOTH_BUTTERFLY_RIGHT",
"BOTH_WALL_RUN_RIGHT",
"BOTH_WALL_RUN_RIGHT_FLIP",
"BOTH_WALL_RUN_RIGHT_STOP",
"BOTH_WALL_RUN_LEFT",
"BOTH_WALL_RUN_LEFT_FLIP",
"BOTH_WALL_RUN_LEFT_STOP",
"BOTH_WALL_FLIP_RIGHT",
"BOTH_WALL_FLIP_LEFT",
"BOTH_KNOCKDOWN1",
"BOTH_KNOCKDOWN2",
"BOTH_KNOCKDOWN3",
"BOTH_KNOCKDOWN4",
"BOTH_KNOCKDOWN5",
"BOTH_GETUP1",
"BOTH_GETUP2",
"BOTH_GETUP3",
"BOTH_GETUP4",
"BOTH_GETUP5",
"BOTH_GETUP_CROUCH_F1",
"BOTH_GETUP_CROUCH_B1",
"BOTH_FORCE_GETUP_F1",
"BOTH_FORCE_GETUP_F2",
"BOTH_FORCE_GETUP_B1",
"BOTH_FORCE_GETUP_B2",
"BOTH_FORCE_GETUP_B3",
"BOTH_FORCE_GETUP_B4",
"BOTH_FORCE_GETUP_B5",
"BOTH_FORCE_GETUP_B6",
"BOTH_GETUP_BROLL_B",
"BOTH_GETUP_BROLL_F",
"BOTH_GETUP_BROLL_L",
"BOTH_GETUP_BROLL_R",
"BOTH_GETUP_FROLL_B",
"BOTH_GETUP_FROLL_F",
"BOTH_GETUP_FROLL_L",
"BOTH_GETUP_FROLL_R",
"BOTH_WALL_FLIP_BACK1",
"BOTH_WALL_FLIP_BACK2",
"BOTH_SPIN1",
"BOTH_CEILING_CLING",
"BOTH_CEILING_DROP",
"BOTH_FJSS_TR_BL",
"BOTH_FJSS_TL_BR",
"BOTH_RIGHTHANDCHOPPEDOFF",
"BOTH_DEFLECTSLASH__R__L_FIN",
"BOTH_BASHED1",
"BOTH_ARIAL_F1",
"BOTH_BUTTERFLY_FR1",
"BOTH_BUTTERFLY_FL1",
"BOTH_BACK_FLIP_UP",
"BOTH_LOSE_SABER",
"BOTH_STAFF_TAUNT",
"BOTH_DUAL_TAUNT",
"BOTH_A6_FB",
"BOTH_A6_LR",
"BOTH_A7_HILT",
"BOTH_ALORA_SPIN",
"BOTH_ALORA_FLIP_1",
"BOTH_ALORA_FLIP_2",
"BOTH_ALORA_FLIP_3",
"BOTH_ALORA_FLIP_B",
"BOTH_ALORA_SPIN_THROW",
"BOTH_ALORA_SPIN_SLASH",
"BOTH_ALORA_TAUNT",
"BOTH_ROSH_PAIN",
"BOTH_ROSH_HEAL",
"BOTH_TAVION_SCEPTERGROUND",
"BOTH_TAVION_SWORDPOWER",
"BOTH_SCEPTER_START",
"BOTH_SCEPTER_HOLD",
"BOTH_SCEPTER_STOP",
"BOTH_KYLE_GRAB",
"BOTH_KYLE_MISS",
"BOTH_KYLE_PA_1",
"BOTH_PLAYER_PA_1",
"BOTH_KYLE_PA_2",
"BOTH_PLAYER_PA_2",
"BOTH_PLAYER_PA_FLY",
"BOTH_KYLE_PA_3",
"BOTH_PLAYER_PA_3",
"BOTH_PLAYER_PA_3_FLY",
"BOTH_BUCK_RIDER",
"BOTH_HOLD_START",
"BOTH_HOLD_MISS",
"BOTH_HOLD_IDLE",
"BOTH_HOLD_END",
"BOTH_HOLD_ATTACK",
"BOTH_HOLD_SNIFF",
"BOTH_HOLD_DROP",
"BOTH_GRABBED",
"BOTH_RELEASED",
"BOTH_HANG_IDLE",
"BOTH_HANG_ATTACK",
"BOTH_HANG_PAIN",
"BOTH_HIT1",
"BOTH_LADDER_UP1",
"BOTH_LADDER_DWN1",
"BOTH_LADDER_IDLE",
"BOTH_FLY_SHIELDED",
"BOTH_SWIM_IDLE1",
"BOTH_SWIMFORWARD",
"BOTH_SWIMBACKWARD",
"BOTH_SLEEP1",
"BOTH_SLEEP6START",
"BOTH_SLEEP6STOP",
"BOTH_SLEEP1GETUP",
"BOTH_SLEEP1GETUP2",
"BOTH_CHOKE1START",
"BOTH_CHOKE1STARTHOLD",
"BOTH_CHOKE1",
"BOTH_CHOKE2",
"BOTH_CHOKE3",
"BOTH_POWERUP1",
"BOTH_TURNON",
"BOTH_TURNOFF",
"BOTH_BUTTON1",
"BOTH_BUTTON2",
"BOTH_BUTTON_HOLD",
"BOTH_BUTTON_RELEASE",
"BOTH_RESISTPUSH",
"BOTH_FORCEPUSH",
"BOTH_FORCEPULL",
"BOTH_MINDTRICK1",
"BOTH_MINDTRICK2",
"BOTH_FORCELIGHTNING",
"BOTH_FORCELIGHTNING_START",
"BOTH_FORCELIGHTNING_HOLD",
"BOTH_FORCELIGHTNING_RELEASE",
"BOTH_FORCEHEAL_START",
"BOTH_FORCEHEAL_STOP",
"BOTH_FORCEHEAL_QUICK",
"BOTH_SABERPULL",
"BOTH_FORCEGRIP1",
"BOTH_FORCEGRIP3",
"BOTH_FORCEGRIP3THROW",
"BOTH_FORCEGRIP_HOLD",
"BOTH_FORCEGRIP_RELEASE",
"BOTH_TOSS1",
"BOTH_TOSS2",
"BOTH_FORCE_RAGE",
"BOTH_FORCE_2HANDEDLIGHTNING",
"BOTH_FORCE_2HANDEDLIGHTNING_START",
"BOTH_FORCE_2HANDEDLIGHTNING_HOLD",
"BOTH_FORCE_2HANDEDLIGHTNING_RELEASE",
"BOTH_FORCE_DRAIN",
"BOTH_FORCE_DRAIN_START",
"BOTH_FORCE_DRAIN_HOLD",
"BOTH_FORCE_DRAIN_RELEASE",
"BOTH_FORCE_DRAIN_GRAB_START",
"BOTH_FORCE_DRAIN_GRAB_HOLD",
"BOTH_FORCE_DRAIN_GRAB_END",
"BOTH_FORCE_DRAIN_GRABBED",
"BOTH_FORCE_ABSORB",
"BOTH_FORCE_ABSORB_START",
"BOTH_FORCE_ABSORB_END",
"BOTH_FORCE_PROTECT",
"BOTH_FORCE_PROTECT_FAST",
"BOTH_WIND",
"BOTH_STAND_TO_KNEEL",
"BOTH_KNEEL_TO_STAND",
"BOTH_TUSKENATTACK1",
"BOTH_TUSKENATTACK2",
"BOTH_TUSKENATTACK3",
"BOTH_TUSKENLUNGE1",
"BOTH_TUSKENTAUNT1",
"BOTH_COWER1_START",
"BOTH_COWER1",
"BOTH_COWER1_STOP",
"BOTH_SONICPAIN_START",
"BOTH_SONICPAIN_HOLD",
"BOTH_SONICPAIN_END",
"BOTH_STAND10",
"BOTH_STAND10_TALK1",
"BOTH_STAND10_TALK2",
"BOTH_STAND10TOSTAND1",
"BOTH_STAND1_TALK1",
"BOTH_STAND1_TALK2",
"BOTH_STAND1_TALK3",
"BOTH_SIT4",
"BOTH_SIT5",
"BOTH_SIT5_TALK1",
"BOTH_SIT5_TALK2",
"BOTH_SIT5_TALK3",
"BOTH_SIT6",
"BOTH_SIT7",
"TORSO_DROPWEAP1",
"TORSO_DROPWEAP4",
"TORSO_RAISEWEAP1",
"TORSO_RAISEWEAP4",
"TORSO_WEAPONREADY1",
"TORSO_WEAPONREADY2",
"TORSO_WEAPONREADY3",
"TORSO_WEAPONREADY4",
"TORSO_WEAPONREADY10",
"TORSO_WEAPONIDLE2",
"TORSO_WEAPONIDLE3",
"TORSO_WEAPONIDLE4",
"TORSO_WEAPONIDLE10",
"TORSO_SURRENDER_START",
"TORSO_SURRENDER_STOP",
"TORSO_CHOKING1",
"TORSO_HANDSIGNAL1",
"TORSO_HANDSIGNAL2",
"TORSO_HANDSIGNAL3",
"TORSO_HANDSIGNAL4",
"TORSO_HANDSIGNAL5",
"LEGS_TURN1",
"LEGS_TURN2",
"LEGS_LEAN_LEFT1",
"LEGS_LEAN_RIGHT1",
"LEGS_CHOKING1",
"LEGS_LEFTUP1",
"LEGS_LEFTUP2",
"LEGS_LEFTUP3",
"LEGS_LEFTUP4",
"LEGS_LEFTUP5",
"LEGS_RIGHTUP1",
"LEGS_RIGHTUP2",
"LEGS_RIGHTUP3",
"LEGS_RIGHTUP4",
"LEGS_RIGHTUP5",
"LEGS_S1_LUP1",
"LEGS_S1_LUP2",
"LEGS_S1_LUP3",
"LEGS_S1_LUP4",
"LEGS_S1_LUP5",
"LEGS_S1_RUP1",
"LEGS_S1_RUP2",
"LEGS_S1_RUP3",
"LEGS_S1_RUP4",
"LEGS_S1_RUP5",
"LEGS_S3_LUP1",
"LEGS_S3_LUP2",
"LEGS_S3_LUP3",
"LEGS_S3_LUP4",
"LEGS_S3_LUP5",
"LEGS_S3_RUP1",
"LEGS_S3_RUP2",
"LEGS_S3_RUP3",
"LEGS_S3_RUP4",
"LEGS_S3_RUP5",
"LEGS_S4_LUP1",
"LEGS_S4_LUP2",
"LEGS_S4_LUP3",
"LEGS_S4_LUP4",
"LEGS_S4_LUP5",
"LEGS_S4_RUP1",
"LEGS_S4_RUP2",
"LEGS_S4_RUP3",
"LEGS_S4_RUP4",
"LEGS_S4_RUP5",
"LEGS_S5_LUP1",
"LEGS_S5_LUP2",
"LEGS_S5_LUP3",
"LEGS_S5_LUP4",
"LEGS_S5_LUP5",
"LEGS_S5_RUP1",
"LEGS_S5_RUP2",
"LEGS_S5_RUP3",
"LEGS_S5_RUP4",
"LEGS_S5_RUP5",
"LEGS_S6_LUP1",
"LEGS_S6_LUP2",
"LEGS_S6_LUP3",
"LEGS_S6_LUP4",
"LEGS_S6_LUP5",
"LEGS_S6_RUP1",
"LEGS_S6_RUP2",
"LEGS_S6_RUP3",
"LEGS_S6_RUP4",
"LEGS_S6_RUP5",
"LEGS_S7_LUP1",
"LEGS_S7_LUP2",
"LEGS_S7_LUP3",
"LEGS_S7_LUP4",
"LEGS_S7_LUP5",
"LEGS_S7_RUP1",
"LEGS_S7_RUP2",
"LEGS_S7_RUP3",
"LEGS_S7_RUP4",
"LEGS_S7_RUP5",
"LEGS_TURN180",
"BOTH_CIN_1",
"BOTH_CIN_2",
"BOTH_CIN_3",
"BOTH_CIN_4",
"BOTH_CIN_5",
"BOTH_CIN_6",
"BOTH_CIN_7",
"BOTH_CIN_8",
"BOTH_CIN_9",
"BOTH_CIN_10",
"BOTH_CIN_11",
"BOTH_CIN_12",
"BOTH_CIN_13",
"BOTH_CIN_14",
"BOTH_CIN_15",
"BOTH_CIN_16",
"BOTH_CIN_17",
"BOTH_CIN_18",
"BOTH_CIN_19",
"BOTH_CIN_20",
"BOTH_CIN_21",
"BOTH_CIN_22",
"BOTH_CIN_23",
"BOTH_CIN_24",
"BOTH_CIN_25",
"BOTH_CIN_26",
"BOTH_CIN_27",
"BOTH_CIN_28",
"BOTH_CIN_29",
"BOTH_CIN_30",
"BOTH_CIN_31",
"BOTH_CIN_32",
"BOTH_CIN_33",
"BOTH_CIN_34",
"BOTH_CIN_35",
"BOTH_CIN_36",
"BOTH_CIN_37",
"BOTH_CIN_38",
"BOTH_CIN_39",
"BOTH_CIN_40",
"BOTH_CIN_41",
"BOTH_CIN_42",
"BOTH_CIN_43",
"BOTH_CIN_44",
"BOTH_CIN_45",
"BOTH_CIN_46",
"BOTH_CIN_47",
"BOTH_CIN_48",
"BOTH_CIN_49",
"BOTH_CIN_50",
"MAX_ANIMATIONS",
"MAX_TOTALANIMATIONS"
};