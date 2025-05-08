using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class DialogueUI : MonoBehaviour
{

    public static DialogueUI Instance;
    public GameObject dialoguePanel;
    public TMP_Text dialogueText;

    private void Awake()
    {
        if (Instance == null) Instance = this;
        else Destroy(gameObject);

        dialoguePanel.SetActive(false);
    }
    
    private void Update()
    {
        if (dialoguePanel.activeSelf && Input.GetKeyDown(KeyCode.Return))//if dialogue is active we can use esc to hide it
        {
            Debug.Log("Check");
            HideDialogue();
        }
    }


    public void ShowDialogue(string message)
    {
        Debug.Log("Showing dialogue: " + message); // Add this
        dialoguePanel.SetActive(true);
        dialogueText.text = message;
    }

    public void HideDialogue()
    {
        dialoguePanel.SetActive(false);
    }
}
