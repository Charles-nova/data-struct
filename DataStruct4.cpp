// DataStruct4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max 13 
#define infinity 10000 //定义无穷大
#define ERROR -1
#define OK 1



typedef struct {
    int  arcs[max][max];
    int vexnum, arcnum;
}MGraph; //定义图
typedef struct {
    bool path[max][max];
}PathMatrix;
typedef struct {
    int length[max];
}short_path_table;
typedef struct {
    int road;
    int node_num;
}node;

//初始化图
int Initgraph(MGraph& map) {
    map.arcs[0][1] = 18;map.arcs[0][2] = 22;
    map.arcs[1][0] = 18;map.arcs[1][3] = 27;map.arcs[1][4] = 19; 
    map.arcs[2][0] = 22; map.arcs[2][4] = 4;
    map.arcs[3][1] = 27; map.arcs[3][6] = 4;
    map.arcs[4][1] = 19; map.arcs[4][2] = 4; map.arcs[4][5] = 32; map.arcs[4][6] = 23;
    map.arcs[5][4] = 32; map.arcs[5][8] = 4;
    map.arcs[6][3] = 4; map.arcs[6][4] = 23; map.arcs[6][7] = 4; map.arcs[6][9] = 15;
    map.arcs[7][6] = 4; map.arcs[7][10] = 43; map.arcs[7][12] = 21;
    map.arcs[8][5] = 4; map.arcs[8][9] = 8; map.arcs[8][12] = 14;
    map.arcs[9][8] = 8; map.arcs[9][6] = 15; map.arcs[9][11] = 21;
    map.arcs[10][7] = 43; map.arcs[10][12] = 20;
    map.arcs[11][9] = 21; map.arcs[11][12] = 30;
    map.arcs[12][8] = 14; map.arcs[12][11] = 30; map.arcs[12][7] = 21; map.arcs[12][10] = 20;
    map.vexnum = max; map.arcnum = max;
    return OK;
}


int Match(char *str) {
    int matchnum = 0;
    if (!strcmp(str, "北门"))matchnum = 0;
    else if (!strcmp(str, "饮水思源"))matchnum = 1;
    else if (!strcmp(str, "传送门3"))matchnum = 2;
    else if (!strcmp(str, "传送门1"))matchnum = 3;
    else if (!strcmp(str, "腾飞塔"))matchnum = 4;
    else if (!strcmp(str, "传送门4"))matchnum = 5;
    else if (!strcmp(str, "图书馆"))matchnum = 6;
    else if (!strcmp(str, "传送门2"))matchnum = 7;
    else if (!strcmp(str, "宪梓堂"))matchnum = 8;
    else if (!strcmp(str, "教学主楼"))matchnum = 9;
    else if (!strcmp(str, "西迁馆"))matchnum = 10;
    else if (!strcmp(str, "活动中心"))matchnum = 11;
    else if (!strcmp(str, "南门"))matchnum = 12;
    else {
        return ERROR;
    }
    return matchnum;
}

void shortest_path_DIJ(MGraph& map1, int start1, int end1, PathMatrix &path, short_path_table &len) {
    int v = 0; int final[max] = { 0 }; int w = 0; int i = 0; int min = 0; int j = 0;
    for (v = 0; v < map1.vexnum; v++) {
        final[v] = false; len.length[v] = map1.arcs[start1][v];
        for (w = 0; w < map1.vexnum; w++) path.path[v][w] = false;
        if (len.length[v] < infinity) {
            path.path[v][start1] = true;
            path.path[v][v] = true;
        }
    }
    len.length[start1] = 0; final[start1] = true;
    //开始主循环
    for (i = 1; i < map1.vexnum; i++) {
        min = infinity;
        for (w = 0; w < map1.vexnum; w++) {
            if (!final[w])
                if (len.length[w] < min) {
                    v = w; min = len.length[w];
                }
        }
        final[v] = true;
        for (w = 0; w < map1.vexnum; w++) {
            if (!final[w] && (min + map1.arcs[v][w] < len.length[w])) {
                len.length[w] = min + map1.arcs[v][w];
                for (j = 0; j < map1.vexnum; j++) {
                    path.path[w][j] = path.path[v][j];
                }
                path.path[w][w] = true;
            }
        }
    }
}

//定义找到最短路径的函数并且打印出来
int print_node(int i) {
    switch (i) {
    case 0:
        printf("%s", "北门");
        break;
    case 1:
        printf("%s", "饮水思源");
        break;
    case 2:
        printf("%s", "传送门3");
        break;
    case 3:
        printf("%s", "传送门1");
            break;
    case 4:
        printf("%s", "腾飞塔");
            break;
    case 5:
        printf("%s", "传送门4");
            break;
    case 6:
        printf("%s", "图书馆");
        break;
    case 7:
        printf("%s", "传送门2");
        break;
    case 8:
        printf("%s", "宪梓堂");
        break;
    case 9:
        printf("%s", "教学主楼");
        break;
    case 10:
        printf("%s", "西迁馆");
        break;
    case 11:
        printf("%s", "活动中心");
        break;
    case 12:
        printf("%s", "南门");
        break;
    }
    return OK;
}

int print_path(MGraph Map,PathMatrix& found_path ,int end, short_path_table& len) {
    int i = 0; int path_len = 0; node* final_path = NULL; int counter = 0;
    int j = 0; int k=0;
    for (i = 0; i < max; i++) {
        if (found_path.path[end][i] == true) {
            path_len++;
        }
    }
    final_path = (node*)malloc((path_len + 1) * sizeof(node));
    if (final_path == NULL)return ERROR;
    for (i = 0; i < max; i++) {
        if (found_path.path[end][i] == true) {
            final_path[counter].road = len.length[i];
            final_path[counter].node_num = i;
            counter++;
        }
    }
    node temp;
    temp.node_num = 0;
    temp.road = 0;
    for (i = 0; i < path_len; i++) {
        k = i;
        for (j = i; j < path_len; j++) {
            if (final_path[k].road > final_path[j].road)k = j;
        }
        temp.node_num = final_path[i].node_num;
        temp.road = final_path[i].road;
        final_path[i].node_num= final_path[k].node_num;
        final_path[i].road= final_path[k].road;
        final_path[k].node_num = temp.node_num;
        final_path[k].road = temp.road;
    }
    for (i = 0; i < path_len; i++) {
        print_node(final_path[i].node_num);
        printf("%s", " ");
    }
    if (final_path != NULL)free(final_path);
    return OK;
}
int main(int argc, char** argv)
{
    if (argc != 3) {
        printf("%s", "ERROR_01");
        return 0;
    }
    MGraph xjtu; PathMatrix path_matrix;// 定义如果p[v][w]为TRUE,则w为v0到v最短路径的顶点
    short_path_table shortest_length;
    int i = 0; int j = 0;
    int start = 0; int end = 0;
    xjtu.arcnum = 0; xjtu.vexnum = 0;
    for (i = 0; i < max; i++) {
        for (j = 0; j < max; j++) {
            xjtu.arcs[i][j] = infinity;      //初始化
            path_matrix.path[i][j] = false;
            shortest_length.length[i] = 0;
        }
    }
    Initgraph(xjtu);
    start = Match(argv[1]);
    end = Match(argv[2]);
    if((start==ERROR)||(end==ERROR)){
        printf("%s", "ERROR_02");
        return 0;
    }
    shortest_path_DIJ(xjtu, start, end, path_matrix, shortest_length);
    if (shortest_length.length[end] == infinity) {
        printf("%s", "ERROR_02");
        return 0;
    }
    printf("%d", shortest_length.length[end]);
    //print_path(xjtu,path_matrix, end, shortest_length);
    return 0;
}


