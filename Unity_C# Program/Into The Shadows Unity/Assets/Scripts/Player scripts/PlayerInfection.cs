using TMPro; // Make sure you have this namespace for TextMeshPro
using UnityEngine;
using UnityEngine.UI; // Needed for UI elements
public class PlayerInfection : MonoBehaviour
{
    public HealthBar healthBar;
    public GameObject restartButton;
    public GameObject infectionPopup;
    public static bool gameOver = false;
    public static float currentInfection = 0.0f; // Current infection level
    public float maxInfection = 100.0f; // Max infection level
    public TextMeshProUGUI gameOverText; // Use TextMeshProUGUI for TextMeshPro

    void Start()
    {
        currentInfection = 0f;
    }
    // void Update()
    // {
    // Increase the infection level
    public void IncreaseInfection(float amount)
    {
        currentInfection += amount;
        currentInfection = Mathf.Clamp(currentInfection, 0, maxInfection); // Prevent overflow
        healthBar.UpdateInfectionBar(currentInfection);

        Debug.Log("Infection Level: " + currentInfection);

        if (currentInfection >= maxInfection)
        {
            Debug.Log("Player is fully infected!");
            TriggerGameOver();
        }
    }

    // Trigger the Game Over UI
    public void TriggerGameOver()
    {
        gameOver = true;
        if (gameOverText != null)
        {
            gameOverText.enabled = true; // Enable the Game Over text
        }
        // Optionally, pause the game or handle further logic here
        Time.timeScale = 0f; // Freeze time (game pause)
        restartButton.SetActive(true);
        Cursor.lockState = CursorLockMode.None; //cursor lock to window
        Cursor.visible = true;
        infectionPopup.SetActive(false);
        }
    // }
}
