using System.Collections;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;

public class TextController : MonoBehaviour
{
    public TMP_Text storyText;      
    public string[] lines;          
    public float fadeTime = 0.5f;   
    public float displayTime = 2f;  
    public string nextSceneName = "Merge";
    public AudioSource audioSource;
    public AudioClip startClip;
    void Start()
    {
        StartCoroutine(PlayTextSequence());
    }

    IEnumerator PlayTextSequence()
    {
        if(audioSource != null){
            audioSource.Play();
        }
        
        foreach (var line in lines)
        {
            storyText.text = line;
            yield return FadeText(0, 1);
            yield return new WaitForSeconds(displayTime);
            yield return FadeText(1, 0);
        }
        SceneManager.LoadScene(nextSceneName);
        gameObject.SetActive(false);

    }

    IEnumerator FadeText(float from, float to)
    {
        float t = 0;
        while (t < fadeTime)
        {
            t += Time.deltaTime;
            storyText.alpha = Mathf.Lerp(from, to, t / fadeTime); //fades text
            yield return null;
        }
        storyText.alpha = to;
    }
}
