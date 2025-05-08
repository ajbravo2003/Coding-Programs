using UnityEngine;
using UnityEngine.SceneManagement;

public class restart : MonoBehaviour
{
    public void RestartScene()
    {
        SceneManager.LoadScene("Merge");
    }

    public void skipSplash(){
        SceneManager.LoadScene("IntroScene");
    }
}
