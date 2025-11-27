#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// [구조체 정의] 응원가 데이터를 담을 노드
typedef struct SongNode {
    char name[50];      // 선수 이름
    char lyrics[1000];  // 응원가 가사 (줄바꿈 포함)
    struct SongNode* next; // 다음 노드를 가리키는 포인터
} SongNode;

// 함수 선언
void add_song(SongNode** head, const char* name, const char* lyrics);
void search_song(SongNode* head);
void delete_song(SongNode** head);
void print_all_songs(SongNode* head);
void free_all(SongNode* head);
void init_data(SongNode** head); // 초기 데이터 로드

int main() {
    SongNode* head = NULL; // 리스트의 시작점 (초기엔 비어있음)
    int choice;

    // 1. 초기 데이터(사용자가 주신 가사) 로드
    init_data(&head);

    printf("⚾ SSG 랜더스 응원가 관리 프로그램 ⚾\n");

    while (1) {
        printf("\n==================================\n");
        printf("1. 응원가 검색 (이름 입력)\n");
        printf("2. 새 응원가 추가\n");
        printf("3. 응원가 삭제\n");
        printf("4. 전체 목록 보기\n");
        printf("0. 종료\n");
        printf("==================================\n");
        printf("메뉴 선택 >> ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // 입력 버퍼 비우기 (필수!)

        switch (choice) {
            case 1:
                search_song(head);
                break;
            case 2: {
                char name[50], lyrics[1000];
                printf("선수 이름: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // 엔터 제거

                printf("가사 입력 (한 줄로 입력해주세요): ");
                fgets(lyrics, sizeof(lyrics), stdin);
                lyrics[strcspn(lyrics, "\n")] = 0;

                add_song(&head, name, lyrics);
                printf("✅ 추가되었습니다!\n");
                break;
            }
            case 3:
                delete_song(&head);
                break;
            case 4:
                print_all_songs(head);
                break;
            case 0:
                printf("프로그램을 종료합니다. 메모리를 정리합니다...\n");
                free_all(head);
                return 0;
            default:
                printf("잘못된 입력입니다.\n");
        }
    }
}

// [기능 1] 응원가 추가 (동적 메모리 할당)
// 리스트의 맨 마지막에 노드를 연결합니다.
void add_song(SongNode** head, const char* name, const char* lyrics) {
    // 1. 새로운 노드 생성 (malloc)
    SongNode* newNode = (SongNode*)malloc(sizeof(SongNode));
    if (newNode == NULL) {
        printf("메모리 부족 오류!\n");
        return;
    }
    
    // 2. 데이터 복사
    strcpy(newNode->name, name);
    strcpy(newNode->lyrics, lyrics);
    newNode->next = NULL; // 마지막 노드니까 다음은 없음

    // 3. 리스트에 연결
    if (*head == NULL) {
        // 리스트가 비어있으면 이 노드가 헤드(첫 번째)가 됨
        *head = newNode;
    } else {
        // 리스트 끝까지 가서 연결
        SongNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// [기능 2] 응원가 검색
void search_song(SongNode* head) {
    char target[50];
    printf("검색할 선수 이름: ");
    fgets(target, sizeof(target), stdin);
    target[strcspn(target, "\n")] = 0;

    SongNode* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, target) == 0) {
            printf("\n🎵 [%s] 선수의 응원가 🎵\n", temp->name);
            printf("-----------------------------\n");
            printf("%s\n", temp->lyrics);
            printf("-----------------------------\n");
            return;
        }
        temp = temp->next;
    }
    printf("❌ '%s' 선수의 응원가를 찾을 수 없습니다.\n", target);
}

// [기능 3] 응원가 삭제 (메모리 해제 포함)
void delete_song(SongNode** head) {
    char target[50];
    printf("삭제할 선수 이름: ");
    fgets(target, sizeof(target), stdin);
    target[strcspn(target, "\n")] = 0;

    SongNode* curr = *head;
    SongNode* prev = NULL;

    // 리스트 순회
    while (curr != NULL) {
        if (strcmp(curr->name, target) == 0) {
            // 찾았다!
            if (prev == NULL) {
                // 삭제하려는 게 첫 번째 노드일 때
                *head = curr->next;
            } else {
                // 중간이나 끝 노드일 때 (이전 노드를 다음 노드와 연결)
                prev->next = curr->next;
            }
            free(curr); // 메모리 반납 (중요!)
            printf("🗑️ [%s] 응원가가 삭제되었습니다.\n", target);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("❌ 삭제할 대상을 찾을 수 없습니다.\n");
}

// [기능 4] 전체 목록 출력
void print_all_songs(SongNode* head) {
    SongNode* temp = head;
    int count = 1;
    printf("\n--- 저장된 응원가 목록 ---\n");
    while (temp != NULL) {
        printf("%d. %s\n", count++, temp->name);
        temp = temp->next;
    }
}

// [종료] 모든 메모리 해제
void free_all(SongNode* head) {
    SongNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// [초기 데이터] 보내주신 가사를 미리 넣어두는 함수
void init_data(SongNode** head) {
    add_song(head, "박지환", "랜더스 박지환 안타를 날려라 워어어 워어어 워어어\n랜더스 박지환 승리를 위하여 워어어 워어어 워어어 (박지환!)");
    add_song(head, "박성한", "박성한! 랜더스 위하여 시원하게 날려라\n오오오~ 오오오오~ (x2)");
    add_song(head, "정준재", "오 안타 정준재~ 치고 달려 정준재~\n오 안타 정준재~ 랜더스의 정준재~\n오 오오오오오~ 치고 달려 정준재~");
    add_song(head, "김찬형", "오! 안타 김찬형(짝짝)(x2)\n오오오오 랜더스 위해 안타 김찬형~ (x2)");
    add_song(head, "김성현", "랜더스의 김성현 날려버려 김성현\n아아아아아아아아 안타! 오오오오오오오오 안타! (x2)");
    add_song(head, "최준우", "랜더스 최준우~ 안타! 오오오오 오오오~\n랜더스 최준우~ 안타! 오오오오 최~준우 (x2)");
    add_song(head, "안상현", "오오오 오오오 랜더스의 안상현\n오오오 오오오 치!고 달려라~ (x2)");
    add_song(head, "하재훈", "랜더스의! 하재훈 안타 워어어어어 하재훈 안타\n랜더스의! 하재훈 안타 승리를 위해 하재훈 안타 (x2)");
    add_song(head, "최정", "빠바바바바밤 최! 빠바바바바밤 정!\n빰빠라바라바라밤 최! 정! 홈! 런! (x4)");
    add_song(head, "고명준", "아~~~~~ 고명준 오오오 오~(x3)\n랜더스의 고명준! (x2)");
    add_song(head, "조형우", "조형우 워어어어 시원하게 날려라\n워어어어 짜릿하게 넘겨라 워어어어 랜더스~ 조형우~ (x2)");
    add_song(head, "김민식", "오! 김민식 안타 워 워어어어~\n오! 김민식 안타 워어~ 워어어어~ (x2)");
    add_song(head, "신범수", "열!쩡! 신범수 오오오오오(안타!) (x4)");
    add_song(head, "에레디아", "랜더스 에레디아 안타 에헤라디아\n랜더스 에레디아 워우워어어 (x2) 에!레!디아!");
    add_song(head, "이정범", "워~ 워워워워~ 랜더스~ 이~정범~\n워~ 워워워 워워워~ 안타 날려버려~ (x2)");
    add_song(head, "한유섬", "야~ 야~ 야~ 야~ 한유섬 날려버려라(홈런!) (x2)\n한유섬 날려버려라 (x2)");
    add_song(head, "오태곤", "오! 안타 오태곤 오오오~ 오오오~\n오! 안타 오태곤 오오오오 랜더스의 승리 위해~ (x2)");
    add_song(head, "류효승", "랜더스 류효승 오 오오오\n오오오 오오오 랜더스 류효승 (x2)");
    add_song(head, "김성욱", "김~성욱 랜더스를 위해 날려라 워어어~ 랜더스 김성욱~ 안!타!\n김~성욱 랜더스를 위해 달려라 워어어~ 랜더스 김성욱~ 김성욱!");
    add_song(head, "최지훈", "최지훈 안타! 최지훈 안타! 오오 오 오오오~\n최지훈 안타! 최지훈 안타! 랜더스의 승리 위하여~ (x2)");
    add_song(head, "김성민", "김성민 날려라~ 오오오오오~\n김성민~ 오! 안타 날려라~ (x2)");
    add_song(head, "이지영", "SSG 안방마님 이지영 안타!\n오 랜더스의 이지영 안타! 안타를 날려줘요~ 이야이야이야이야~ (x2)");
    add_song(head, "김창평", "김창평 안타 김창평 안타 랜더스의 김창평 (x4)");
}
