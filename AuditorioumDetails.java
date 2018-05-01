
import java.util.ArrayList;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author User
 */
class mypair {

    int v1, v2;

    mypair(int a, int b) {
        v1 = a;
        v2 = b;
    }
}

public class AuditorioumDetails {

    int status;// 0 pending 1 accepted 2 cancel
    int startt;
    int endt;
    String requesterid;
    String subject;
    String picloc;
    String reservetionid;

    AuditorioumDetails() {
        status = startt = endt = 0;
        requesterid = subject =picloc=reservetionid= "N/A";
    }

    boolean isfree(ArrayList<AuditorioumDetails> arr, int st, int ed,int needl,int needh)
    {
        int hp = 24 * 60 + 10;
        int[] flag = new int[hp];
        for (int i = 0; i < st; i++) {
            flag[i] = 1;
        }
        for (int i = ed + 1; i < hp; i++) {
            flag[i] = 1;
        }

        for (int i = 0; i < arr.size(); i++) {
            AuditorioumDetails tt = arr.get(i);
            int ss = tt.startt, ee = tt.endt;
            for (int k = ss; k <= ee; k++) {
                flag[i] = 1;
            }
        }
        
        for(int i=needl;i<=needh;i++)
        {
            if(flag[i]==1)
            {
                return false;
            }
        }
        
        return true;
    }
    
    ArrayList<mypair> audfreeslots(ArrayList<AuditorioumDetails> arr, int st, int ed) {
        ArrayList<mypair> vec = new ArrayList<>();
        int hp = 24 * 60 + 10;
        int[] flag = new int[hp];
        for (int i = 0; i < st; i++) {
            flag[i] = 1;
        }
        for (int i = ed + 1; i < hp; i++) {
            flag[i] = 1;
        }

        for (int i = 0; i < arr.size(); i++) {
            AuditorioumDetails tt = arr.get(i);
            int ss = tt.startt, ee = tt.endt;
            for (int k = ss; k <= ee; k++) {
                flag[i] = 1;
            }
        }

        int ss = -1, ee = 0, cc = 1;

        for (int i = st; i <= ed; i++) {
            if (flag[i] == 0) {
                ss = i;
                break;
            }
        }
        if (ss == -1) {
            return vec;
        }

        boolean isCum = true;
        int t = 0;

        for (int i = ss; i <= ed + 1; i++) {
            if (isCum) {
                if (flag[i]==0) {
                    ee = i;
                } else {
                    vec.add(new mypair(ss,ee));
                    isCum = false;
                }

            } else {
                if ( flag[i] == 0) {
                    ss = i;
                    ee = i;
                    isCum = true;
                }
            }
        }

        return vec;
    }
}
