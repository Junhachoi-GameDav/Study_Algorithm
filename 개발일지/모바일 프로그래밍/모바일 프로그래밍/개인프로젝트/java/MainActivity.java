package com.example.mobile_programming_test1;

import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;

import java.util.Random;

public class MainActivity extends AppCompatActivity {

    private ImageView card1;
    private ImageView card2;
    private ImageView card3;
    private TextView fortuneText;

    //전역변수
    int ran_num;

    private String[] tarotCardDescriptions = {
            "The Fool (광대): \n\n의미: 새로운 시작, 모험, 무책임함.\n\n해석: 새로운 여정을 시작하거나 무책임한 행동에 주의",
            "The Magician (마술사): \n\n의미: 창조력, 자기 표현, 주도성.\n\n해석: 내면의 에너지를 활용하여 목표를 달성",
            "The High Priestess (교황): \n\n의미: 직관, 숨겨진 지식, 여성성.\n\n해석: 직감력을 발휘하고 숨겨진 지식을 탐험",
            "The Empress (여제): \n\n의미: 풍요, 창조성, 안정.\n\n해석: 안정적인 환경에서 창조성을 표현하고 풍요로운 삶",
            "The Emperor (황제): \n\n의미: 권위, 조직, 규율.\n\n해석: 리더십과 규율을 통해 목표를 달성",
            "The Hierophant (법황): \n\n의미: 전통, 교육, 도덕.\n\n해석: 교육, 전통, 도덕적 가르침에 의한 지혜",
            "The Lovers (연인): \n\n의미: 사랑, 관계, 결합.\n\n해석: 사랑과 관계의 중요성, 결정을 내리는 시기",
            "The Chariot (정복자): \n\n의미: 승리, 힘, 목표 달성.\n\n해석: 의지와 힘을 통해 목표를 달성하고 승리",
            "Strength (힘): \n\n의미: 인내, 용기, 힘.\n\n해석: 어려움에 대한 인내, 내면의 힘을 발휘",
            "The Hermit (은둔자): \n\n의미: 명상, 내적 탐구, 지혜.\n\n해석: 외로움을 통한 내면의 탐험과 깨달음",
            "Wheel of Fortune (운명의 바퀴): \n\n의미: 운명, 변화, 운.\n\n해석: 운명의 바퀴가 돌아가며 새로운 기회와 변화가 옴",
            "Justice (정의): \n\n의미: 공평, 균형, 정의.\n\n해석: 공평하게 판단하고 균형을 유지하는 데 중요성",
            "The Hanged Man (매달린 남자): \n\n의미: 희생, 자기 희생, 변형.\n\n해석: 일시적인 희생을 통해 새로운 시각과 변화",
            "Death (죽음): \n\n의미: 변화, 새로운 시작, 변형.\n\n해석: 끝과 시작, 새로운 생명의 시작",
            "Temperance (절제): \n\n의미: 균형, 조화, 중재.\n\n해석: 간극을 좁히고 조화를 찾아가는 중재",
            "The Devil (악마): \n\n의미: 타락, 결합, 유혹.\n\n해석: 속박과 유혹에 주의하며 해방을 찾기",
            "The Tower (타워): \n\n의미: 파괴, 변화, 결합.\n\n해석: 급격한 변화와 파괴로 인한 새로운 출발",
            "The Star (별): \n\n의미: 희망, 영감, 성공.\n\n해석: 희망과 영감을 찾아나가며 성공을 향해 나아가기",
            "The Moon (달): \n\n의미: 비명, 불확실성, 진실.\n\n해석: 감정적인 변화와 진실을 찾는 여정",
            "The Sun (태양): \n\n의미: 행복, 성공, 에너지.\n\n해석: 밝고 긍정적인 에너지와 성공적인 기간",
            "Judgement (심판): \n\n의미: 판단, 부활, 결정.\n\n해석: 지혜로운 판단과 새로운 부활, 결정의 시기",
            "The World (세계): \n\n의미: 완성, 성취, 통합.\n\n해석: 목표 달성과 세계적인 통합의 상징"
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        card1 = findViewById(R.id.card1);
        card2 = findViewById(R.id.card2);
        card3 = findViewById(R.id.card3);
        fortuneText = findViewById(R.id.fortuneText);
    }

    public void onCardClick(View view) {
        ImageView selectedCard = (ImageView) view;
        int cardIndex = -1;

        // 카드 순서
        if (selectedCard.getId() == R.id.card1) {
            cardIndex = 0;
        }
        else if (selectedCard.getId() == R.id.card2){
            cardIndex = 1;
        }
        else {
            cardIndex = 2;
        }

        if (cardIndex != -1) {
            // 랜덤한 카드 이미지로 변경
            int randomCardDrawable = getRandomCardDrawable();
            selectedCard.setImageResource(randomCardDrawable);

            // 운세 텍스트 업데이트
            fortuneText.setText(tarotCardDescriptions[ran_num]);
        }
    }

    private int getRandomCardDrawable() {
        int[] cardDrawables = {
                R.drawable.the_fool_1,
                R.drawable.the_magician_2,
                R.drawable.the_high_priestess_3,
                R.drawable.the_empress_4,
                R.drawable.the_emperor_5,
                R.drawable.the_hierophant_6,
                R.drawable.the_lovers7,
                R.drawable.the_chariot_8,
                R.drawable.the_strength_9,
                R.drawable.the_hermit_10,
                R.drawable.the_wheel_of_fortune_11,
                R.drawable.the_justice_12,
                R.drawable.the_hanged_man13,
                R.drawable.the_death_14,
                R.drawable.the_temperance_15,
                R.drawable.the_devil_16,
                R.drawable.the_tower_17,
                R.drawable.the_star_18,
                R.drawable.the_moon_19,
                R.drawable.the_sun_20,
                R.drawable.the_judgement_21,
                R.drawable.the_world_22
        };

        Random random = new Random();
        int randomIndex = random.nextInt(cardDrawables.length);
        ran_num =randomIndex;
        return cardDrawables[randomIndex];
    }
}

