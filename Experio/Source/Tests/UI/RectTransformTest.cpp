/*
	GameObject root;
	root.rectTransform = RectTransform(FVector2(0, 0), FVector2(100, 100), FVector2(0.5, 0.5));
	root.rectTransform.anchorType = EAnchorType::Full;
	root.isUI = true;

	GameObject child;
	child.rectTransform = RectTransform(FVector2(-10, -15), FVector2(-10, -15));
	child.rectTransform.anchorType = EAnchorType::Full;
	GameObject::Reparent(&root, &child);
	child.isUI = true;

	GameObject grandchild;
	grandchild.rectTransform = RectTransform(FVector2(-10, -10), FVector2(-10, -10));
	grandchild.rectTransform.anchorType = EAnchorType::Full;
	GameObject::Reparent(&child, &grandchild);
	grandchild.isUI = true;

	FRect worldspaceRect = grandchild.GetCanvasSpaceRect();
*/