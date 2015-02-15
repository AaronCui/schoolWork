using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class scoreManager : MonoBehaviour {

	private GameObject director;
	private GameObject player;
	Text instruction;

	// Use this for initialization
	void Start () {
		director = GameObject.FindGameObjectWithTag("Director");
		player = director.GetComponent<GameDirector>().player;
		instruction = GetComponent<Text>();
	}
	
	// Update is called once per frame
	void Update () {
		instruction.text = ("score :" + Mathf.Floor(getDist ()));
	}

	float getDist(){
		return Vector3.Magnitude(player.transform.position);
	}
}
