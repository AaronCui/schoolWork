using UnityEngine;
using System.Collections;

public class Obstacles : MonoBehaviour {
	private GameObject director;
	private GameObject player;
	// Use this for initialization
	void Start () {
		director = GameObject.FindGameObjectWithTag ("Director");
		player = director.GetComponent<GameDirector>().player;
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
