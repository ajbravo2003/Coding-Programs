using UnityEngine;
using TMPro; 

public class infectionPopup : MonoBehaviour
{
    public CanvasGroup popupCanvasGroup;

    public float fadeDuration = 0.5f;    // How fast it fades in/out
    public float displayDuration = 1.5f; // How long it stays fully visible

    private float lastInfectionLevel = 0f;
    private bool isShowing = false;

    private void Start()
    {
        popupCanvasGroup.alpha = 0f; // Start fully invisible
        lastInfectionLevel = PlayerInfection.currentInfection;//gets player infection rate
    }

    private void Update()
    {
        // Detect infection rising
        if (PlayerInfection.currentInfection > lastInfectionLevel)
        {
            ShowPopup();
            lastInfectionLevel = PlayerInfection.currentInfection;
        }
    }

    public void ShowPopup()
    {
        if (!isShowing)
        {
            StartCoroutine(FadePopup());
        }
    }

    private System.Collections.IEnumerator FadePopup()
    {
        isShowing = true;

        // Fade In
        float elapsed = 0f;
        while (elapsed < fadeDuration)
        {
            elapsed += Time.deltaTime;
            popupCanvasGroup.alpha = Mathf.Lerp(0f, 1f, elapsed / fadeDuration);
            yield return null;
        }
        popupCanvasGroup.alpha = 1f;
        yield return new WaitForSeconds(displayDuration);
        // Fade Out
        elapsed = 0f;
        while (elapsed < fadeDuration)
        {
            elapsed += Time.deltaTime;
            popupCanvasGroup.alpha = Mathf.Lerp(1f, 0f, elapsed / fadeDuration);
            yield return null;
        }
        popupCanvasGroup.alpha = 0f;

        isShowing = false;
    }
}
