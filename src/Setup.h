#ifndef _Setup_h_
#define _Setup_h_

#define version "version 2.5"

#define game_amount 8


#define 빙글_감속비율_빠르게 1.06
#define 빙글_빙글횟수_빠르게 90

#define 빙글_감속비율_중간 1.05
#define 빙글_빙글횟수_중간 115


#define 빙글_감속비율_느리게 1.04
#define 빙글_빙글횟수_느리게 120

#define 당겨_난이도_상 30
#define 당겨_난이도_중 70
#define 당겨_난이도_하 90

#define 던져_난이도_상 14
#define 던져_다트속도_상 6

#define 던져_난이도_중 11
#define 던져_다트속도_중 4

#define 던져_난이도_하 8
#define 던져_다트속도_하 2

short hold_;
short roll_; double roll_speed; unsigned short roll_cnt; unsigned short roll_alpha; unsigned short roll_show;
short pull_; unsigned short Pull_Speed; unsigned short Pull_Extract_Speed; unsigned short Glove_color;
short puzzle_;
short dart_; unsigned short Dart_Speed; unsigned short Dart_ThrowSpeed;
short rhythm_; unsigned short rhythm_max; unsigned short rhythm_tut; unsigned short rhythm_good; unsigned short rhythm_perfect; unsigned short rhythm_wrong;
short memorize_;
short basket_; unsigned short basket_Speed; unsigned short basket_interval; unsigned short basket_color;
short number_; unsigned short number_range; unsigned short number_life;
#endif