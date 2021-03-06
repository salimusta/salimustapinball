//Menu buttons
#define leftBoutonPin 6
#define rightBoutonPin 7
#define OkBoutonPin 8
#define BackBoutonPin 10

//LED MATRIX MANAGEMENT
#define SCREEN_SALIMUSTAPINBALL 0
#define SCREEN_GETREADY 1
#define SCREEN_GO 2
#define SCREEN_MULTIBALL 3
#define SCREEN_PSIT_ANIM 4
#define SCREEN_BALLLEFT 5
#define SCREEN_GAMEOVER 6
#define SCREEN_FULL 7
#define SCREEN_YOUHAVE 8
#define SCREEN_XBALLS 9
#define SCREEN_SCORE 10
#define SCREEN_BALL_INTO_HOLE 11
#define SCREEN_ROSW1 12
#define SCREEN_ROSW2 13
#define SCREEN_ROSW3 14
#define SCREEN_MIDDLE_SHOT 15
#define SCREEN_RED_SHOT 16
#define SCREEN_GREEN_SHOT 17
#define SCREEN_3BUMPERS_MODE 18
#define SCREEN_3BUMPERS_MODE_STATE 19
#define SCREEN_3BUMPERS_MODE_SUCCESS 20
#define SCREEN_GREEN_TARGET_MODE 21
#define SCREEN_GREEN_TARGET_MODE_STATE 22
#define SCREEN_ALL_GATES 23
#define SCREEN_RED_TARGET_MODE 24
#define SCREEN_RED_TARGET_MODE_STATE 25
#define SCREEN_MIDDLE_TARGET_MODE 26
#define SCREEN_MIDDLE_TARGET_MODE_STATE 27
#define SCREEN_BALL_GAME 28
#define SCREEN_BALL_GAME_INTRO 29
#define SCREEN_BUMPERS_RESULT 30
#define SCREEN_TARGETS_RESULT 31
#define SCREEN_SCORE_RESULT 33
#define SCREEN_ALL_TARGET_MODE_STATE 34
#define SCREEN_ALL_TARGET_MODE 35
#define SCREEN_PSIT_MODE_ACTIVE 36
#define SCREEN_PSIT_MODE_STATE 37
#define SCREEN_PSIT_MODE_COMPLETE 38
#define SCREEN_HIGHSCORES 39
#define SCREEN_ENTER_NAME 40
#define SCREEN_WORD_GAME 41
#define SCREEN_STARWARS_INTRO 42
#define SCREEN_STARWARS_GAME 43
#define SCREEN_STARWARS_WIN 44
#define SCREEN_STARWARS_LOST 45
#define SCREEN_STARWARS_INTRO_2 46
#define SCREEN_PLAYER_SCORES 47
#define SCREEN_PLAYER_SELECTION 48
#define SCREEN_PLAYER_WIN 49
#define SCREEN_SUPER_PSIT 50
#define SCREEN_SUPER_PSIT_COMPLETE 51
#define SCREEN_KO1_MULTIBALL 52
#define SCREEN_RAMP_MISSED 53
#define SCREEN_RAMP_SUCCEED 54
#define SCREEN_MODE_DOUBLE_INTRO 55
#define SCREEN_MODE_DOUBLE_STATE 56
#define SCREEN_MODE_DOUBLE_COMPLETE 57
#define SCREEN_MODE_DOUBLE_IDLE 58
#define SCREEN_SCORE_SAVED 59
#define SCREEN_TILT_WARNING 60
#define SCREEN_TILT_ACTIVE 61

#define PRIORITY_LOW 0
#define PRIORITY_HIGH 1

//LIGHT MANAGEMENT
#define ANIM_ALL 1
#define ALL_ANIM_OFF 2
#define VERT_SNAKE_ALL 81
#define ALL_IDLE 82
#define VERT_SNAKE_KEEP_ALL 83

#define FLASH_TOP_LIGHTS 3
#define LIGHT_TOP_LIGHTS 4
#define ALTERN_TOP_LIGHTS 5
#define OFF_TOP_LIGHTS 6
#define DUAL_SNAKE_TOP_LIGHTS 79
#define SNAKE_TOP_LIGHTS 89

#define SNAKE_RIGHT_GREEN_TARGET 7
#define BLINK_RIGHT_GREEN_TARGET 8
#define OFF_RIGHT_GREEN_TARGET 9
#define DATA_RIGHT_GREEN_TARGET 84

#define SNAKE_LEFT_GREEN_TARGET 10
#define BLINK_LEFT_GREEN_TARGET 11
#define OFF_LEFT_GREEN_TARGET 12
#define DATA_LEFT_GREEN_TARGET 85

#define SNAKE_RIGHT_RED_TARGET 13
#define BLINK_RIGHT_RED_TARGET 14
#define OFF_RIGHT_RED_TARGET 15
#define DATA_RIGHT_RED_TARGET 86

#define SNAKE_LEFT_RED_TARGET 16
#define BLINK_LEFT_RED_TARGET 17
#define OFF_LEFT_RED_TARGET 18
#define DATA_LEFT_RED_TARGET 87

#define SNAKE_YELLOW_TARGET 19
#define BLINK_YELLOW_TARGET 20
#define OFF_YELLOW_TARGET 21
#define DATA_YELLOW_TARGET 88

#define ALL_MODE_OFF 22
#define ALL_MODE_ON 77
#define MODE_3_BUMPERS 23
#define MODE_5_MIDDLE 24
#define MODE_GREEN_TARGETS 25
#define MODE_EXTRA_BALL 26
#define MODE_ALL_TARGETS 27
#define MODE_DOUBLE 28
#define MODE_RED_TARGETS 29
#define MODE_PSIT 30
#define SNAKE_MODES 31
#define BLINK_MODES 32

#define ALL_LETTERS_OFF 33
#define ALL_LETTERS_ON 34
#define LETTER_P_ON 35
#define LETTER_S_ON 36
#define LETTER_I_ON 37
#define LETTER_T_ON 38

#define BLINK_LETTER_P 39
#define BLINK_LETTER_S 40
#define BLINK_LETTER_I 41
#define BLINK_LETTER_T 42

#define LETTER_P_OFF 43
#define LETTER_S_OFF 44
#define LETTER_I_OFF 45
#define LETTER_T_OFF 46
#define SNAKE_LETTERS 47

#define ALL_BUMPERS_OFF 48
#define BUMPER_1_ON 49
#define BUMPER_2_ON 50
#define BUMPER_3_ON 51
#define BLINK_BUMPER_1 52
#define BLINK_BUMPER_2 53
#define BLINK_BUMPER_3 54
#define BUMPER_1_OFF 55
#define BUMPER_2_OFF 56
#define BUMPER_3_OFF 57
#define ALL_BUMPERS_ON 58
#define SNAKE_BUMPERS 80

#define ALL_GATES_ON 59
#define ALL_GATES_OFF 60
#define GATE_1_ON 61
#define GATE_2_ON 62
#define GATE_3_ON 63
#define GATE_1_OFF 64
#define GATE_2_OFF 65
#define GATE_3_OFF 66

#define SNAKE_LAUNCHER 67
#define LAUNCHER_OFF 68

#define LOOSE_OFF 69
#define BLINK_LOOSE 70

#define KO1_OFF 71
#define BLINK_KO1 72
#define SNAKE_KO1 73
#define DATA_KO1 90

#define KO2_OFF 74
#define BLINK_KO2 75
#define SNAKE_KO2 76

#define START_ON 91
#define START_BLINK 92
#define START_OFF 93

//Light 2 Management
#define RAMPGATE_OFF 10
#define RAMPGATE_SNAKE 11
#define RAMPGATE_BLINK 12
#define RAMPGATE_ON 13
#define RAMPGATE_DUAL_SNAKE 14
#define RAMPGATE_ALTERNATE 15

#define RAMP_OFF 20
#define RAMP_ON 21
#define RAMP_BLUE 22
#define RAMP_YELLOW 23
#define RAMP_SNAKE_BLUE 24
#define RAMP_SNAKE_YELLOW 25
#define RAMP_SNAKE 26
#define RAMP_BLINK 27
#define RAMP_ALTERNATE 28



//AMBI LIGHTS
#define RED_ON 1
#define RED_OFF 2
#define GREEN_ON 3
#define GREEN_OFF 4
#define YELLOW_ON 5
#define YELLOW_OFF 6
#define BLUE_ON 7
#define BLUE_OFF 8
#define ALL_ON 9
#define ALL_OFF 10
#define ANIME_ALL 11
#define WHITE_ON 12
#define WHITE_OFF 13
#define BOOST_ON 14
#define BOOST_OFF 15
#define COIN_ON 16
#define COIN_OFF 17

#define GATE_ON 18
#define GATE_OFF 19
#define GATE_ONE_BALL 20

#define FLASH_WHITE 100
#define SNAKE_ALL_COLORS 101

//defines
#define BUMPER_2 1
#define KICKOUT_RELEASE_1 2
#define KICKOUT_CATCH_1 3
#define KICKOUT_RELEASE_2 4
#define LOOSE_BADLY 5
#define BUMPER_1 6
#define ALARM_MODE 7
#define BUMPER_3 8
#define LOOSE_SINGE 9
#define CAFARTE 10
#define LOOSE_BYE_BYE 11
#define GATE_BUZZ 12
#define TARGET_1 13
#define LOOSE_POINT_POINT 14
#define LAUGH_1 15
#define TARGET_BAM 16
#define BOINNG 17
#define TARGET_2 18
#define RED_TARGET_ROUND 19

#define MIDDLE_TARGET_ROUND 20
#define PSIT_MODE 21
#define GREEN_TARGETS_ROUND 22
#define BUMPERS_ROUND 23
#define MIDDLE_SHOT_ROUND 24
#define EXTRABALL_ROUND 25
#define PSIT 26
#define ANADINMI 27
#define JAVOO_SALIM 28
#define GATE1 29
#define GATE2 30
#define GATE3 31
#define DESIREHEY 32
#define HITALLTHETARGETUCAN 33
#define KABOOM 34
#define CANDOBETTER 35
#define GRANDMOTHER 36
#define MERRYCHRISTMASLOOSER 37
#define OMGYOUWON_HIGHSCORE 38
#define ONEMOREFOREXTRAPOINT 39
#define PSITSUCCESS5000 40
#define RIREBOTH 41
#define RIREDESIREE 42
#define RIRESALIM 43
#define WHATASHOT 44
#define OUCH 45
#define STILLWAITING 46
#define WANG 47
#define WAW 48
#define WAWWHATASHOT 49
#define WHYDIDUDOTHAT 50
#define WOULDUBEWONDERMAN 51
#define YOUHITTHATRIGHT 52
#define YOUMOVE 53
#define YOURETHEHERO 54
#define BIGEXPLOSION 55
#define BLASTER 56
#define PETITEEXPLOSION 57
#define DARTHVADORFAIL 58
#define THREEBUMPERS 59
#define BIP 60
#define PIECE 61
#define RICOCHET 62
#define VALIDATION 63
#define YIHHA 64
#define DOUBLE_ROUND_INTRO 65
#define EVERYTHING_DOUBLED 66
#define NOPE 67
#define SHOOT_THE_RAMP 68
#define SUPER_PSIT_MODE 69
#define GAME_OVER 70
#define BALL_LOOSE 71
#define CAISSE 72
#define TILT_SOUND 73
#define START_SOUND 74
#define GET_READY 75
#define GO_SOUND 76
#define MULTIBALL_SOUND 77
#define PLAYER_1 78
#define PLAYER_2 79
#define PLAYER_3 80
#define PLAYER_4 81

#define JIVE_BUNNY 100
#define FALLIN_RAIN 101
#define SURFIN_USA 102
#define MISIRLOU 103
#define ELVIS 104
#define FINDERSKEEPERS 105
#define ROCKNROLLPARTY 106
#define CANCANYOU 107
#define NOBLESURFER 108
#define TWISTPARTY 109
#define SHUTDOWN 110
#define BUSINESS 111
#define FISHBONE 112
#define CUBA 113
#define HIDEHO 114
#define HEY 115
#define RELAX 116
#define STARWARSTHEME 117
#define JAZZ 118
#define MISSION_IMPOSSIBLE 119
#define CANCAN_SPEED 120




//MODES----------------
#define NO_MODE 0
#define BUMPERS_MODE 1
#define GREEN_TARGET_MODE 2
#define RED_TARGET_MODE 3
#define MIDDLE_TARGET_MODE 4
#define EXTRA_BALL_MODE 5
#define ALL_TARGET_MODE 6
#define WORD_GAME_MODE 7
#define STARWARS_MODE 8
#define DOUBLE_MODE 9

//DATA FOR THE LED MATRIX--------------
#define COUNTDOWN 0
#define BUMPER_STATUS 1
#define NB_HITS 2
#define FLIPPERS_STATE 3
#define PSIT_STATE 4
#define PLAYER_SELECTED 5
#define MAX_PLAYER 6

//LED MATRIX TO MASTER COMMAND
#define BALL_BOUNCE 1
#define BALL_CATCHED 2
#define GAME_IDLE 3
#define GAME_LOST 4
#define GAME_WIN 5

#define ENEMI_DESTROYED 6
#define SHIP_DESTROYED 7
#define LASER_SHOT 8
