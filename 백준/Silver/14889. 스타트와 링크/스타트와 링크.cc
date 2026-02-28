#include <iostream>
#include <vector>

using namespace std;

int N; // 축구를 하기 위해 모인 사람들(짝수여야함)
int answer=1e9;
vector<vector<int>> synergyTable;
vector<bool> picked;

// idx: 지금 고려중인 사람 번호, cnt:지금까지 스타트팀에 뽑힌 사람 수
void dfs(int idx, int cnt)
{
    if (cnt == N / 2)
    {
        vector<int> startTeam, linkTeam;
        for (int i = 0; i < N; i++)
        {
            if (picked[i]) startTeam.push_back(i);
            else linkTeam.push_back(i);
        }

        int startScore = 0;
        int linkScore = 0;

        for (int i = 0; i < (int)startTeam.size(); i++)
        {
            for (int j = i + 1; j < (int)startTeam.size(); j++)
            {
                int a = startTeam[i];
                int b = startTeam[j];
                startScore += synergyTable[a][b] + synergyTable[b][a];
            }
        }

        for (int i = 0; i < (int)linkTeam.size(); i++)
        {
            for (int j = i + 1; j < (int)linkTeam.size(); j++)
            {
                int a = linkTeam[i];
                int b = linkTeam[j];
                linkScore += synergyTable[a][b] + synergyTable[b][a];
            }
        }

        int difference = abs(startScore - linkScore);
        answer = min(answer, difference);
        return;
    }

    if (idx == N) return;
    if (cnt + (N - idx) < N / 2) return;

    picked[idx] = true;
    dfs(idx + 1, cnt + 1);

    picked[idx] = false;
    dfs(idx + 1, cnt);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    synergyTable.assign(N, vector<int>(N)); // 시너지 테이블

    picked.assign(N, false); // 스타트팀(false) 인지 링크팀(true)인지 구분지어 집합을 만들기 위함
                                   // 답
    // N의 조건
    if (N >= 4 && N <= 20 && N % 2 == 0)
    {
        // 시너지 표 저장
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> synergyTable[i][j];
            }
        }
        // 한 조합 씩 해 나가보자
        // (1,2) (3,4) || (1,3) (2,4) || (1,4) (2,3) 이 숫자는 사람 이름의 느낌을 표현한 것
        picked[0] = true; // 1번 사람은 무조건 스타트팀에 고정
        dfs(1, 1);        // 조합 하나 뜯어와서 각 팀에 사람 저장
    }
    cout << answer;
}


