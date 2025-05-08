using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.Collections;

public class Flicker : MonoBehaviour
{
    public Image splashImage;

    public GameObject playButton;

    public AudioSource flickerAudio;

    public float flickerDuration = 5f;
    public float flickerInterval = 0.1f;

    void Start()
    {
        splashImage.enabled = true;
        playButton.SetActive(false);

        if (flickerAudio != null)
        {
            flickerAudio.Play();
        }
        playButton.SetActive(true);
        // StartCoroutine(FlickerRoutine());
    }

    // IEnumerator FlickerRoutine()
    // {
    //     // float startTime = Time.time;

    //     // while (Time.time - startTime < flickerDuration)
    //     // {
    //     //     splashImage.enabled = !splashImage.enabled;
    //     //     yield return new WaitForSeconds(flickerInterval);
    //     // }

    //     // splashImage.enabled = true;
    //     playButton.SetActive(true);

    //     if (flickerAudio != null)
    //     {
    //         flickerAudio.Stop();
    //     }
    // }

    public void OnPlayButtonClicked()
    {
        SceneManager.LoadScene("IntroScene");
    }
}
